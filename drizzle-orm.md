## Apply SQL commands to database
```typescript
import { sql } from "drizzle-orm";
import { db } from "@/server/db";
import fs from "fs";
import path from "path";

// changes.sql contains sql queries to be executed
// path is relative to place from where this file will be executed
const filePath = path.join(__dirname, "changes.sql");

async function applySqlFile(filePath: string) {
  try {
    // Read the SQL file
    const sqlContent = fs.readFileSync(filePath, "utf-8");

    // Split the content by semicolons to separate individual SQL statements
    const queries = sqlContent
      .split(";")
      .map((query) => {
        // Remove full-line comments and empty lines, but preserve inline comments
        const processedQuery = query
          .split("\n")
          .filter((line) => {
            const trimmedLine = line.trim();
            return !(trimmedLine === "" || trimmedLine.startsWith("--"));
          })
          .join("\n");

        return processedQuery.trim();
      })
      .filter((query) => query.trim() !== "");

    // Execute each query
    for (const query of queries) {
      await db.execute(sql.raw(query));
      console.info(`Executed query: ${query.trim()}`);
    }

    console.info("All queries executed successfully");
    process.exit(0);
  } catch (error) {
    console.error("Error executing SQL file:", error);
    process.exit(1);
  }
}

void applySqlFile(filePath);
```
## Types Retrieval
### InferSelectModel - get names and types of all columns of table
```typescript
import { type InferSelectModel } from "drizzle-orm";
import type { bank_account } from "@/server/db/drizzle/schema.ts/schema";
export type details1 = {
  // get names and types of all columns of 'bank_account' table
  bankDetails: InferSelectModel<typeof bank_account>;
};
```
### GetColumnData - get type of column
- https://github.com/drizzle-team/drizzle-orm/blob/main/drizzle-orm/src/column.ts#L138
```typescript
import type { GetColumnData } from "drizzle-orm";
import type { beneficiary } from "@/server/db/drizzle/schema.ts/schema";

export type Benificiary1 = {
  id: number;
  name: string | null;
  // get types of 'status' column on 'beneficiary' table
  status: GetColumnData<typeof beneficiary.status>;
}[]; 
```
