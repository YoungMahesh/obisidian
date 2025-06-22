- Large Language Models (LLMs) are advanced artificial intelligence systems designed to understand and generate human language
- They are built on deep learning techniques, specifically using a type of neural network architecture known as transformer models
- The term 'Large' refers to the extensive datasets on which these models are trained

## Transformer architecture

- Transformers are a type of neural network architecture introduced in the paper "Attention is All You Need" by Vaswani et al. in 2017. They rely entirely on attension mechanisms to draw relationships between different parts of the input sequence, eliminating the need for recurrent layers that were common in previous sequence-to-sequence models.
- revolutionized the file of Natural Language Processing (NLP) and is the foundation for models like BERT and many modern Large Language Models (LLMs)

### key components and concepts

    1. Attention Mechanism
    - The core of the Transformer is the attention mechanism. It allows the model to focus on different parts of the input sequence when processing it
    - Specifically, the scaled dot-product attention is used. It computes attention weights by taking the dot product of the query with all the keys, dividing by the square root of the dimension of the keys (to prevent excessively large values), and applying a softmax function.

## other

### techniques to optimize the performance of the model

- prompting: multi-shot; chaining and tools
  - fast to implement; low cost
  - limited by context length; slower, expensive inference
- RAG
  - accuracy improvement with low data needs, scalable, efficient
  - harder than prompt, lack nuance
- fine-tuning
  - deep expertise & specialist knowledge, nuance, learn a different tone/style, faster and cheaper inference
  - need significant effort and resources to implement; high data needs; risk of 'catastrophic forgetting'

### inference

- process of generating responses or predictions based on the input provided by the user
- process
  1.  input reception: the model receives a prompt or query
  2.  tokenization: the input is broken down into tokens, which are the smallest units of meaning that the model can understand
  3.  response generation: using complex probabilistic computations, the model generates a response by selecting the most likely next token based on the learned patterns
