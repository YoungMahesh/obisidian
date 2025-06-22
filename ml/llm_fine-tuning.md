# Theory

## Types

- Supervised Fine turning
  - most common method
  - model is trained on a labeled dataset specific to a target task, such as text classification or named entity recognition
  - goal is to enhance the model's performance on that task by providing it with relevant examples
- few-shot learning
  - provides a limited number of examples to guide the model
  - helps model understand the task context without extensive fine-tuning
- transfer learning
  - leverages knowledge gained from training on large, general dataset and applies it to a related but different task
  - e.g. using a model trained on general text data and applying it to a specific legal text classification task by fine tuning it with a smaller dataset of legal documents, thus leveraging its prior knowledge
- domain-specific fine-tuning
  - model is fine tuned on a dataset that is specific to a particular industry or domain
  - e.g. medical chatbots or legal document analysis
- parameter-based fine-tuning
  - adjusting the parameters of a pre-trained model using domain-specific data
    - end-to-end training: updating all parameters of the model
    - selective layer training: adjusting only specific layers to improve task performance
- feature-based fine-tuning
  - the pre-trained model's features are extracted and used by other machine learning models for specific tasks
  - e.g. extracing features from a pre-trained image classification model and using these features as inputs for a new clasifier that predicts specific types of defects in manaufacturing processes
- instruction fine-tuning
  - focuses on training models using explicit instructions or prompts, helping them to understand how to respond to various queries or tasks effectively
- parameter-efficient fine-tuning (PEFT)
  - updates only a small subset of parameters during training, significantly reducing memory and computational requirements compared to full fine-tuning methods
  - techiques such as [Low-Rank Adaptation (LoRA)](/ai/llama_fine-tuning.md) exemplify this approach
- sequential fine-tuning
  - involves adapting a model to a series of related tasks in stages, allowing it to build proficiency across multiple specialized areas while retaining broader knowledge
  - e.g. first fine-tuning a model on general news articles, then sequentially adapting it to focus on political news and later fine-tuning it further for election-related content
- distillation
  - trains a smaller model to replicate the performance of a larger one, optimizing efficiency and size while maintaining performance levels suitatable for deployment in resource-constrained environments

## Quantization

- A technique aimed at reducing model's size and improving it's computational efficiency by reducing precision of numerical representation of model's parameters
- This process involves converting the model's weights and activations from high-precision formats, such as 32-bit floating point numbers to lower pricision formats like 8-bit integers
  - Benefits
    - faster inference: lower precision calculations can be performed more quickly, enhancing the speed at which models can generate outputs during the inference
    - reduced memory usage: by lowering the precision of weights, quantization reduces the overall size of LLM, allowing them to run on devices with limited memory resources

# Practical

## frontier models

### [OpenAI fine tuning](https://platform.openai.com/docs/guides/fine-tuning)

- [costs](https://platform.openai.com/docs/guides/fine-tuning#estimate-costs)
- openAI models available for fine tuning
- variants of gpt-3.5, gpt-4, gpt-4o
- for most users, gpt-4o-mini is right model in terms of performance, cost and ease of use
- advantages
- ability to train on more examples that can fit in a prompt
- token savings due to shorter prompts

## open-source models

- [Llama Fine Tuning](/ai/llama_fine-tuning.md)
