#database

## concepts
- `drizzle-kit push` = `drizzle-kit generate` + `drizzle-kit migrate`
- you need to create separate `drizzle.config.ts` file for different environments
	- e.g. `drizzle-prod.config.ts` for production, `drizzle-dev.config.ts` for development


## how to apply migrations
### 1. introspect
- purpose: pull schema from database
```bash
# this will pull correct database schema and store it in drizzle-directory in comment form
drizzle-kit introspect

# sync entry of first migration (from database to local) entry of which is 
#   created in _jornal.json with database/__drizzle_migrations table
drizzle-kit migrate
```

- During `drizzle-kit migrate`, you may get error `You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '/*`
- In this case, convert  block-comments (`/* */`) to line comments (`-- `) in `.sql` migration file
- This error happens probably because drizzle-migration engine does not support block-comments

### 2.  generate
- purpose: check difference between local-schema and database-schema
- https://orm.drizzle.team/docs/migrations
```bash
# Currently I don't know which files drizzle-kit compares to generate migration-script
# generate migration script, purpose of this is to create sql statements which
#   on application to database will match schema in schema.ts (value of 
#   schema variable in drizzle-config file)
drizzle-kit generate
```

### 3. migrate
- purpose: sync local and database schema
```bash
# 1. apply sql code generated using `drizzle-kit generate` to database
# 2. register which migrations are applied to database by registering entry of
#   migration from ./drizzle/meta/_journal.json to '__drizzle_migrations' table
#   in database
drizzle-kit migrate
```

### how to apply migration sql queries one at a time

- **NOTE**: You cannot use something like `START TRANSACTION ... COMMIT`  or any other command to either commit all or discard all changes as MySQL does not support rollback for DDL statements such as `CREATE TABLE XYZ`

- **Why**: If we applied all generated sql statements at once, it will be hard to figure which statement is throwing error if some statement is faulty
	- e.g. while dropping index(generated sql-code), you need to drop foreign-key also(not generated but required sql-code)

- **Process**
	- comment out all sql-queries
	- uncomment sql query which we are going to apply now
	- run migration `drizzle-kit migrate` to apply uncommented/active queries to database 
	- comment out applied query and next statement to continue execution
	- To successfully rerun same migration file again and again we will either:
		1. put some code which will cause error after active sql query
			- e.g. `--comment`, no space after `--` hence this line will throw error
		2. delete entry of last migration from `__drizzle-migrations` table created in database to tell `drizzle-kit` that migration is not applied yet

```sql
-- Example of how to apply migrations one statement at a time

-- below script will drop `user1_fk` and provide error, which will stop 
--   sync of `meta/_journal.json` in repository to '__drizzle_migrations' table
--   in database, so that we can run migration script again, by:
--      1) comment-out executed code-block
--      2) un-comment code-block to execute next
alter table user1
drop foreign key `user1_fk`;--> statement-breakpoint

-- comment below is invalid for drizzle migration script as it does not have
--   have <space> after `--`

--alter table user2
--drop foreign key `user2_fk`;
```

### errors during migration
#errors/drizzle
#### syntax error near `/*`
- drizzle-migration does not support block comments, use inline comments : two hyphens followed by a space (`-- `)

#### syntax error near `<start of sql-query>` , after `;`
- drizzle migration expect ending of statement with `;--> statement-breakpoint` instead of just `;`

#### cannot drop index needed in a foreign key constraint
- drop foreign-key then index
- `drizzle-kit` generate to recreate foreign keys again if needed

```sql
alter table beneficiary
drop foreign key `xyz_fk`,
drop index `xyz_idx`;--> statement-breakpoint
```

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
