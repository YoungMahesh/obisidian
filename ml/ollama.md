```bash
ollama run <model-name>   # run model, download if not availalbe
ollama list

# inside ollama chat
/help
/clear # clear current session
/show info
```

### frontends
- [msty](https://msty.app)

### REST api
by default ollama runs a local server at: `http://localhost:11434`

main endpoints
- generate a completion: `POST /api/generate`
- generate a chat completion: `POST /api/chat`

```python
import requests

# Base URL
BASE_URL = "http://localhost:11434/api"

# Generate a completion
def generate_completion(model, prompt):
    response = requests.post(f"{BASE_URL}/generate", json={
        "model": model,
        "prompt": prompt
    })
    return response.json()

# Chat completion
def generate_chat(model, messages):
    response = requests.post(f"{BASE_URL}/chat", json={
        "model": model,
        "messages": messages
    })
    return response.json()

# Example usage
completion = generate_completion("llama2", "Tell me a short joke")
chat_response = generate_chat("llama2", [
    {"role": "user", "content": "Hello, how are you?"}
])
```

### Modelfile

a blueprint for creating and customizing language models in Ollama
It's similar to Dockerfile but specifically designed for AI models. It allows you to:

- specifiy a base model
- set custom parameters
- define system prompts
- customize model behavior

```modelfile
# https://ollama.readthedocs.io/en/modelfile/#format

FROM llama3.2
# temperature: Controls creativity (higher = more creative)
PARAMETER temperature 1

# num_ctx: Sets context window size
PARAMETER num_ctx 4096

SYSTEM You are Mario from super mario bros, acting as an assistant.

# trimple quotes for multi-line prompt
SYSTEM """
You are an AI assistant designed to help users.
Your responses should be:
- Helpful
- Concise
- Accurate
"""
```

```bash
ollama create my-mario-model -f ./Modelfile
ollama show --modelfile <model-name>
ollama run my-mario-model
```

## Theory

### parameters

parameters are the internal variables of a machine learning model that are learning during the training process.

- **Analogy**: parameters as Recipe Ingredients. Imagine Neural network is like a complex recipe:

  - Parameters are like the precise amount of ingredients
  - The more parameters, the more nuanced and detailed the 'recipe' can be

- More parameters ≠ Always better
- Quality of training data matters more than pure parameter count

### context length

maximum number of tokens (words or word parts) a language model can process and "remember" in a single in a single interaction.

llm respones consume context length.
When context length approaches the limit, oldest messages are progressively removed to ensure model can always process the most
recent conversation

1 token ~= 0.75 words

### embedding length

represents the dimensionality of vector representations that capture semantic meaning of words or tokens in a high-dimensional space.

- **Analogy**: Word embeddings as semantic co-ordination system. Imagine words as points in a complex, multi-dimensional space:
  - Similar words are closer together
  - semantic relationships are represented by vector distances
  - more dimensions allow more nuanced representations

### quantization

compress machine learning models by reducing the precision of model weights, making them more efficient and light weight.

**Analogy: Model Compression like Photo compression**
