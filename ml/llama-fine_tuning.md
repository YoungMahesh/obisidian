## examples

### example 1 - use QLoRA fine-tuning

- here we will reduce size of the original model through qunatization, then apply parameters from another models to make it more
  efficient for a specific task
- so the model in the end will be less in size but more efficient at specific task than original model

```python
# -q = quiet; minimize console output
# --use-deprecated=legacy-resolver - to fix error related to dependency conflicts
!pip install -q fs datasets requests torch peft bitsandbytes transformers trl accelerate sentencepiece --use-deprecated=legacy-resolver

import os
import re
import math
from tqdm import tqdm
from google.colab import userdata
from huggingface_hub import login
import torch
import transformers
from transformers import AutoModelForCausalLM, AutoTokenizer, BitsAndBytesConfig, TrainingArguments, set_seed
from peft import LoraConfig, PeftModel
from datetime import datetime

# constants
BASE_MODEL = "meta-llama/Meta-Llama-3.1-8B"
FINETUNED_MODEL = f"ed-donner/pricer-2024-09-13_13.04.39"

# Hyperparameters for LoRA Fine-Tuning
# r - the inner dimension of the low-rank matrices
# started with 8 then double to 16, then good results with 32
LORA_R = 32
LORA_ALPHA = 64
TARGET_MODULES = ['q_proj', 'v_proj', 'k_proj', 'o_proj']

# login to huggingface by importing it's api key
hf_token = userdata.get('HF_TOKEN')
login(hf_token, add_to_git_credential=True)


# use base model without quantization
# device_map = "auto" means that the model will be loaded on the GPU if it is available
# will get warning that GPU RAM is not enough on free version of google-colab (where GPU RAM is 15GB)
# llama model is gated on huggingface; i will try ollama in future
base_model = AutoModelForCausalLM.from_pretrained(BASE_MODEL, device_map="auto")

# memory footprint of llama 3.1 8B model is ~ 32.1 GB
print(f"Memory footprint: {base_model.get_memory_footprint() / 1e9:,.1f} GB")


# get details of model architecture - embed tokens, decoder layers, activation function, etc
base_model


# load the base model using 8 bit
quant_config = BitsAndBytesConfig(load_in_8bit=True)
base_model = AutoModelForCausalLM.from_pretrained(
  BASE_MODEL,
  quantization_config=quant_config,
  device_map="auto"
)
# ~ 9.1 GB
print(f"Memory footprint: {base_model.get_memory_footprint() / 1e9:,.1f} GB")

# get architecture of quantized base model; you will see there is not difference in architecture of the model
base_model

# load the base model using 4 bit
quant_config = BitsAndBytesConfig(
  load_in_4bit=True,
  bnb_4bit_use_double_quant=True,
  bnb_4bit_compute_dtype=torch.float16,
  bnb_4bit_quant_type="nf4"
)
base_model = AutoModelForCausalLM.from_pretrained(
  BASE_MODEL,
  quantization_config=quant_config,
  device_map="auto"
)
# ~ 5.59 GB
print(f"Memory footprint: {base_model.get_memory_footprint() / 1e9:,.1f} GB")
base_model


# ---------- exploring PEFT (parameter-efficient fine-tuning) models -------------------------
#
# A PEFT model is an approach to fine-tuning LLM which only fine-tunes a small number of additional
#   parameters while keeping the original pre-trained model's parameters frozen
# Main PEFT methods: LoRA (Low-Rank Adaptation), Prefix Tuning, Prompt Tuning, P-Tuning
# load a base model and then apply a PEFT approach to adapt it to a specific task without changing
#   the entire model's parameters
fine_tuned_model = PeftModel.from_pretrained(base_model,FINETUNED_MODEL)
# ~ 5.70 GB; a very small increase in memory footprint compared to base model
print(f"Memory footprint: {fine_tuned_model.get_memory_footprint() / 1e9:,.1f} GB")

# view architecture of fine-tuned model; architecture is now different from base model
# in architecture,you will see additional layers (lora_A, lora_B, etc) in additional to
#   existing layers (base_layer) for decoder layers (q_proj, k_proj, etc) of the model
fine_tuned_model


# each of the target modules has 2 LoRA adapter matrices, called lora_A and lora_B
# these are designed to that weights can be adapted by adding alpha * lora_A * lora_B
# let's calculate the number of weights using their dimensions:

# see the matrix dimensions in the architecture details
lora_q_proj = 4096 * 32 + 4096 * 32
lora_k_proj = 4096 * 32 + 1024 * 32
lora_v_proj = 4096 * 32 + 1024 * 32
lora_o_proj = 4096 * 32 + 4096 * 32

# each layer comes to
lora_layer = lora_q_proj + lora_k_proj + lora_v_proj + lora_o_proj

# there are 32 layers
params = lora_layer * 32

# so the total size in MB is
size = (params * 4) / 1_000_000

# ~  size: 109 MB; you can see this size in huggingface repository of fine-tuned model for file
#   named adapter_model.safetensors (this file store parameters)
print(f"Number of parameters: {params:,}; size: {size:,.1f} MB")

# ---------- summary of what we have done so far -------------------------
# 1. we take original base model of size 32 GB
# 2. we quantized it to 8 bit reducing it's size to ~ 9 GB
# 3. we quantized it to 4 bit reducing it's size to ~ 5.6 GB
# 4. we then apply QLoRA (with r=32) on quantized(4-bit) model increasing size by small amount
#    while making it more efficient to a specific task
```

## considerations before selecting our base model

- number of parameters
- Llama vs Qwen vs Phi vs Gemma
- base or instruct variants

### where to look for base model

On [huggingface open llm leaderboard](https://huggingface.co/spaces/open-llm-leaderboard/open_llm_leaderboard), use filters according to our needs

### example 2

```python
# keep in mind: our base model has 8 billion parameters, quantized down to 4 bits compared with gpt-40 which has TRILLIONS of parameters

!pip install -q datasets==2.21.0 requests torch peft bitsandbytes transformers==4.43.1 trl accelerate sentencepiece tiktoken matplotlib

import os
import re
import math
from tqdm import tqdm
from google.colab import userdata
from huggingface_hub import login
import torch
import transformers
from transformers import AutoModelForCausalLM, AutoTokenizer, BitsAndBytesConfig, TrainingArguments, set_seed
from peft import LoraConfig, PeftModel
from datetime import datetime
from matplotlib.pyplot as plt

# Tokenizers
LLAMA_3_1 = "meta_llama/Meta-Llama-3.1-8B"
QWEN_2_5 = "Qwen/Qwen2.5-7B"
GEMMA_2 = "google/gemma-2-9b"
PHI_3 = "microsoft/Phi-3-medium-4k-instruct"

# constants
BASE_MODEL = LLAMA_3_1
HF_USER = 'ed-donner'
DATASET_NAME = f"{HF_USER}/pricer-data"
MAX_SEQUENCE_LENGTH = 182
QUANT_4_BIT = True

# work in progress

```

## word meanings

- parameters
  - broder term that encompasses all learnable values in a neural network, including weights and biases
  - think of parameters as the entire collection of values that define the network's configuration
- weights
  - specific type of parameter; all weights are parameters
  - represent the strength of connections between neurons in different layers
  - determine how much influence one neuron has on another
  - typically organized in matrices
  - updated during training to minimize the loss function
  - in technique like LoRA, you're specifically manipulating weights while keeping other parameters frozen
- weight and parameters in Llama 3.1 8B model
  - 8B == 8 billion parameters
  - majority of the 8 billion parameters are weight parameters
    - weights include: attention weights, projection matrices, embedding weights
    - not all 8 billion parameters are equally important, LoRA allows fine-tuning by manipulating a small subset of weights
    - typically, you might only train 1-10% of the total parameters during fine-tuning

## LoRA (Low-Rank Adaptation)

- a popular technique for efficiently adapting large language models (LLMs)
- it is an innovative parameter-efficient fine-tuning method designed to reduce the computational and memory costs of adapting
  large neural networks
- problem it solves
  - traditional fine-tuning requires updating all parameters of a large model, which is computationally expensive and memory intensive.
    For massive models like GPT-3, LLaMA with billions of parameters, full fine-tuning is often impractical
- core principle
  - instead of updating all model weights, LoRA introduces small, trainable "rank decomposition" matrices. These matrices are added to
    the original pre-trained model weights during fine-tuning.
- how it works
  - for a weight matrix W, LoRA introduces two smaller matrices: A (low-rank) and B.
  - the update to the original weights becomes: W' = W + BA
  - A and B are much smaller than W, significantly reducing trainable parameters
- limitations
  - performance can be slightly lower than full fine-tuning
  - requires careful selection of rank and adaptation strategy
- best practices
  - start with a low rank (4-16) and increase if needed
  - experiment with different adaptation techniques
  - monitor performance metrics during fine-tuning

## QLoRA - Quantization Low-Rank Adaptation

- combines two powerful techniques: Quantization and Low-Rank Adaptation (LoRA)
- designed to enable fine-tuning of large language models with even more limited computational resources
- keep the number of weights but reduce their precision
- Quantization
  - Reduces model precision from 32-bit floating-point to lower bit-width (e.g. 4-bit)
    - 4 bits are interpreted as float, not int
    - the adapter matrices are still 32-bit
  - dramatically reduces memory requirements
  - minimal performance degradation compared to full-precision models
- LoRA
  - introduces small, trainable LoRA matrices
  - train only these low-rank matrices
  - minimal computational and memory overhead
- advantages
  - enables fine-tuning on consumer-grade hardware
  - reduces memory footprint by 4-10x
  - maintains near-original model performance
  - allows adapation of massive models with limited resources
- best practices
  - start with 4-bit quantization
  - use adaptive optimizers
  - monitor performance metrics
  - experiment with different low-rank matrix sizes

## Hyperparameters

- configuration settings that are set before the learning process begins and control how a machine learning model is trained
- unlike model parameters (like weights and biases), that are learning during training, hyperparameters are set by the machine
  learning engineer to guide the training process
- characteristics
  - set before training begins
  - cannot be directly learned from the data
  - significantly impact model performance
  - typically require manual tuning or automated search techniques
- common types
  - learning rate
    - controls how much the model changes in response to the learned error
    - too high: model might overshoot optimal solution
    - too low: model learns very slowly
  - batch size
    - number of training examples used in each iteration
    - affects training speed and model generalization
    - smaller batches: more noise in gradient estimation
    - larger batches: more stable gradient estimation
  - number of epochs
    - how many times the entiner training dataset is passed through the model
    - too few: underfitting; too many: overfitting
  - network architecture
    - number of layers, number of neurons per layer, activation functions, dropout rates
  - regularization
    - L1/L2 regularization strength, dropout rate, early stopping patience
- key hyperparameters for LoRA fine-tuning
  - 3 essential: rank, alpha, target modules
  - rank (r)
    - the inner dimension of the low-rank matrices
    - typical range: 4-16
    - impact: lower rank (4-8): less computational cost; higher-rank(32-64): more capacity to capture task-specific nuances
    - rule of thumb: start with 8 then double to 16, then 32, until diminishing returns
  - alpha (scaling factor)
    - scaling factor that multiplies the lower rank matrices
    - controls the magnitude of LoRA updates
    - typical range: 8 to 32
    - rule of thumb: 2 times the value of r
    - recommendation: start with 16, adjust based on task complexity
  - target modules
    - which model layers to apply LoRA to
    - common choices
      - for transformer models: `q_proj`, `v_proj`, `k_proj`
      - sometimes include `o_proj`, `down_proj`
    - rule of thumb: target the attention head layers
  - learning rate (α)
    - scaling factor for the low-rank adaptation matrices
    - typical range: 0.1 to 2.0
    - recommendation: start with 1.0, use learning rate scheduling (e.g., cosine decay)
  - dropout rate
    - regularization to prevent overfitting
    - typical range: 0.1 to 0.3
    - recommendation: 0.1 is often a good starting point
  - batch size
    - typical range: 8 to 128
    - depends on: available GPU memory, task complexity, dataset size
  - epochs/training steps
    - typical range: 1 to 5 epochs
    - recommendation: use early stopping and validation monitoring
  ```py
  # example psuedocode configuration
  lora_config = {
    'r': 16, # randk of adaptation
    'lora_alpha': 16, # scaling factor
    'lora_dropout': 0.1, # dropout rate
    'target_modules': ['q_proj', 'v_proj'],
    'learning_rate': 1e-4, # adam learning rate
  }
  ```

## Llama fine-tuning with LoRA

- Llama 3.1 8B architecture consists of 32 groups of modules stacked on top of each other, called 'Llama Decoder Layers'
- Each has self-attention layers, multi-layer perception layers, SiLU activation and layer norm
- These parameters take up 32GB memory (3.1 8B model takes up 32GB, 8B refers to 8-billion parameters), training of it will take way more
  than 32GB memory
- But with LoRA, we can do fine-tuning with limited resources with following steps
  1. freeze the weights, we will not optimize them
  2. select some layers to target, called 'Target Modules'
  3. create new 'adapter' metrices with lower dimensions, fewer parameters
  4. apply these adapters to the Target Modules to adjust them - and these get trained
  - to be more precise, there are infact two LoRA metrices A and B that get applied
