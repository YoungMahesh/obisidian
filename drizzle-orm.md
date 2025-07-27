#database

## concepts
- `drizzle-kit push` = `drizzle-kit generate` + `drizzle-kit migrate`
- you need to create separate `drizzle.config.ts` file for different environments
	- e.g. `drizzle-prod.config.ts` for production, `drizzle-dev.config.ts` for development

## Configuration
```typescript
import { type Config } from "drizzle-kit";
import { env } from "@/env";

// default configuration
export default {
  schema: "./src/server/db/schema.ts",
  dialect: "mysql",
  dbCredentials: {
    url: env.DATABASE_URL,
  },
  tablesFilter: ["v6_*"],
} satisfies Config;

// modications i like to make
export default {
  schema: "./src/server/db/schema.ts",
  dialect: "mysql",
  dbCredentials: {
    url: env.DATABASE_URL,
  },
  // directory to store schema pulled using `bunx drizzle-kit introspect`
  // i use same file for schema and introspect
  out: "./src/server/db",
  introspect: {
    casing: "preserve",
  },
} satisfies Config; 
```

## Syntax
### MySQL row insert Id
- `result.insertId == id-of-inserted-row` according to drizzle-ormv0.30.10 docs (which we are using currently) https://stackoverflow.com/a/78644505

- according to new documentation (which we will use in future) we have to use .returningId - https://orm.drizzle.team/docs/insert#insert-returningid

- upgraded version, but need to fix this: whenever we pull schema, it removes .primaryKey() from id of signature-schema, which removes returning of { id: number} from typescript

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
