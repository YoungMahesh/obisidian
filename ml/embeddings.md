# Practical

## options

### databases to store embeddings

- [chroma](https://www.trychroma.com/)

## scrap data from website to create content

### using Puppeteer

```typescript
const urls = ["https://en.wikipedia.org/wiki/Formula_One"];
for (const url of urls) {
  // https://js.langchain.com/docs/integrations/document_loaders/web_loaders/web_puppeteer/
  const loader = new PuppeteerWebBaseLoader(url, {
    launchOptions: {
      headless: true,
      args: ["--no-sandbox"],
    },
    gotoOptions: { waitUntil: "domcontentloaded" },
    evaluate: async (page, browser) => {
      const result = await page.evaluate(() => document.body.innerHTML);
      await browser.close();
      return result;
    },
  });
  const scrapedContent = await loader.scrape();

  // remove html brackets (<></>) and remove empty lines
  const finalContent = scrapedContent
    .replace(/<[^>]*>?/gm, "")
    .replace(/^\s*[\r\n]/gm, "");
}
```

## convert content to chunks for embedding

### split content into sentences

```typescript
const generateChunks = (input: string): string[] => {
  return input
    .trim()
    .split(".")
    .filter((i) => i !== "");
};
```

### split content into paragraph, sentences, newlines

```typescript
const paragraphs = text.split(/\n\s*\n/);
const chunks: string[] = [];
let currentChunk = "";

for (const paragraph of paragraphs) {
  // If adding this paragraph would exceed maxChunkSize, save current chunk and start new one
  if (
    currentChunk.length + paragraph.length > maxChunkSize &&
    currentChunk.length > 0
  ) {
    chunks.push(currentChunk.trim());
    currentChunk = "";
  }

  // If a single paragraph is longer than maxChunkSize, split it into sentences
  if (paragraph.length > maxChunkSize) {
    const sentences = paragraph.match(/[^.!?]+[.!?]+/g) || [paragraph];
    for (const sentence of sentences) {
      if (
        currentChunk.length + sentence.length > maxChunkSize &&
        currentChunk.length > 0
      ) {
        chunks.push(currentChunk.trim());
        currentChunk = "";
      }
      currentChunk += sentence + " ";
    }
  } else {
    currentChunk += paragraph + "\n\n";
  }
}

if (currentChunk.length > 0) {
  chunks.push(currentChunk.trim());
}

return chunks;
```

### langchain textsplitter

```typescript
// https://js.langchain.com/docs/how_to/contextual_compression/#using-a-vanilla-vector-store-retriever
import { RecursiveCharacterTextSplitter } from "@langchain/textsplitters";
const splitter = new RecursiveCharacterTextSplitter({
  chunkSize: 512,
  chunkOverlap: 100,
});
const chunks = await splitter.splitText(savedContent);
```

## create embedding

### using openAI

- [embedding modes by openAI](https://platform.openai.com/docs/guides/embeddings#embedding-models)

| Model                  | Default Dimensions | Supported Dimensions | Max Tokens | lauched on    |
| ---------------------- | ------------------ | -------------------- | ---------- | ------------- |
| text-embedding-3-large | 3072               | 256, 1024, 3072      | 8191       | december 2022 |
| text-embedding-3-small | 1536               | 512, 1536            | 8191       | january 2024  |
| text-embedding-ada-002 | 1536               | 1536                 | 8191       | january 2024  |

- 1 Token ~= 4 characters in English text
- `text-embedding-3-small`
  - OpenAI's most cost-effective embedding model
  - shows improved accuracy compared to `text-embedding-ada-002`
  - 5 times cheaper than `text-embedding-ada-002`

```typescript
import OpenAI from "openai";
const openai = new OpenAI({ apiKey });
// https://platform.openai.com/docs/guides/embeddings#how-to-get-embeddings
// by default, the length of the embedding vector will be 1536
const response = await openai.embeddings.create({
  model: "text-embedding-3-small",
  input: text,
  encoding_format: "float",
});
return response.data[0].embedding;
```

## store embedding
#database/postgres 
### using postgres with pgvector extension

```yml
# DATABASE_URL=postgresql://postgres:d04c97ee3a8fe3520a82@localhost:5432/<db-name>

services:
  pgvector:
    image: pgvector/pgvector:pg16
    restart: always
    # shared memory size; size of RAM allowed to use by docker-container
    shm_size: 128mb
    environment:
      POSTGRES_USER: postgres
      POSTGRES_PASSWORD: d04c97ee3a8fe3520a82
    ports:
      - "5432:5432"
    volumes:
      - ./data1:/var/lib/postgresql/data
```

```sql
------------- initiate database ----------------
-- 1. create database

-- 2. enable vector extension
CREATE EXTENSION IF NOT EXISTS vector;

-- 3. create table to store embeddings
CREATE TABLE resources (
    id SERIAL PRIMARY KEY,
    content TEXT NOT NULL,
    embedding vector(1536) NOT NULL
);
CREATE INDEX resourcesEmbeddingIndex ON resources USING hnsw (embedding vector_cosine_ops);

------------- extra -----------------------
-- check if vector extension is enabed
SELECT EXISTS(SELECT 1 FROM pg_extension WHERE extname = 'vector');
-- list all extensions
SELECT extname FROM pg_extension;
```

### using astra-db

```typescript
import { DataAPIClient } from "@datastax/astra-db-ts";
const astraDBClient = new DataAPIClient(env.ASTRA_DB_TOKEN);
const astraDb = astraDBClient.db(env.ASTRA_DB_ENDPOINT, {
  namespace: ASTRA_DB_NAMESPACE,
});

// https://platform.openai.com/docs/guides/embeddings#how-to-get-embeddings
// https://docs.datastax.com/en/astra-db-serverless/get-started/concepts.html#popular-embedding-models
await astraDb.createCollection(ASTRA_DB_COLLECTION, {
  vector: {
    // 1536 dimensions are created by model 'text-embedding-3-small' from openai
    dimension: 1536,
    // when to use which metric:
    // "cosine" - Text analysis, semantic search [avoid When vector magnitude is important]
    // "euclidean" - Basic vector encoding, clustering [avoid High-dimensional spaces]
    // "dot_product" - Large-scale similarity search, LLM embeddings [avoid When vectors aren't normalized]
    metric: "dot_product",
  },
});

const insertResp = await collection.insertOne({
  $vector: embedding,
  text: chunk,
});
```

# Theory

Embeddings are mathematical representations that transform complex data like text, images, and audio into dense vectors within a continuous vector space.
These vectors capture the semantic relationships and inherent properties of the data they represent, making them interpretable by machine learning algorithms.

## Key Characteristics

**Vector Representation**

- Each embedding is an array of numbers representing an object's position along multiple dimensions
- Modern models typically use over 1024 dimensions to ensure accuracy and detail[4]
- The closer two embeddings are in this vector space, the more semantically similar they are[1]

**Dimensionality Reduction**
Embeddings convert high-dimensional data into lower-dimensional representations while preserving important relationships and patterns. This reduction makes the data more manageable for machine learning algorithms while retaining crucial semantic information.

## Creation Process

**Training Method**
Embeddings are created through neural networks that learn from data rather than requiring explicit human expertise[1]. The process involves:

- Neural networks process input features through hidden layers
- One of the hidden layers learns to factorize features into vectors
- The model continuously adjusts parameters to minimize differences between predicted and actual values[2]

## Applications

**Primary Use Cases**

- Computer vision applications for object detection and image recognition
- Natural language processing for understanding word relationships
- Graph analysis for detecting patterns in network structures[2]

## Benefits

**Technical Advantages**

- Enable efficient computation through compact, dense data representation
- Reduce the need for manual feature engineering
- Support transfer learning between related tasks
- Provide interpretable representations of complex data relationships[3]

## Future Implications

Embeddings are becoming increasingly crucial for AI transparency and interpretability. By visualizing embeddings, researchers can better understand how AI models perceive and process different data points, offering insights into the traditionally opaque nature of AI systems[5].
