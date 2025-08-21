#database/mysql 

- In MySQL, constraints are rules enforced on data columns to ensure the accuracy, reliability, and integrity of the data in the database. They prevent invalid data from being entered into tables.
- In MySQL, the maximum length for most identifiers—including database, table, column, and constraint names—is 64 characters.
- Each constraint have name, you can give custom name to each constraint except for `PRIMARY KEY` where name is always `PRIMARY`

---

Here are the different types of constraints available in MySQL, from most to least common:
### 1. `PRIMARY KEY`
A `PRIMARY KEY` constraint uniquely identifies each record in a table.

*   **Key Properties:**
    *   Must contain **unique** values.
    *   Cannot contain `NULL` values.
    *   A table can have only **one** `PRIMARY KEY`.
    *   The `PRIMARY KEY` can consist of a single column or multiple columns (a composite key).
*   **Purpose:** To provide a unique identifier for every row, which is essential for joining tables and creating relationships.
*   **Example:**
    ```sql
    CREATE TABLE users (
        id INT PRIMARY KEY,  -- id is the primary key
        username VARCHAR(50) NOT NULL
    );
    ```

### 2. `FOREIGN KEY`
A `FOREIGN KEY` constraint is a key used to link two tables together. It is a field (or collection of fields) in one table that refers to the `PRIMARY KEY` in another table.

*   **Key Properties:**
    *   The table containing the foreign key is called the child table, and the table containing the referenced (primary) key is called the parent table.
    *   It prevents actions that would destroy links between tables, such as deleting a parent row that has child rows referencing it.
*   **Purpose:** To maintain referential integrity between two related tables.
*   **Example:**
    ```sql
    CREATE TABLE orders (
        order_id INT PRIMARY KEY,
        user_id INT,
        order_date DATE,
        CONSTRAINT fk_orders_users
            FOREIGN KEY (user_id) REFERENCES users(id) -- Links to the users table
    );
    ```

### 3. `UNIQUE`
A `UNIQUE` constraint ensures that all values in a column (or a set of columns) are different from one another.

*   **Key Properties:**
    *   Similar to a `PRIMARY KEY`, but a table can have **multiple** `UNIQUE` constraints.
    *   Unlike a `PRIMARY KEY`, a `UNIQUE` constraint **can accept one** `NULL` value (as `NULL` is not equal to any other value, including another `NULL`).
*   **Purpose:** To enforce uniqueness on a column that is not the primary identifier, such as an email address or a username.
*   **Example:**
    ```sql
    CREATE TABLE users (
        id INT PRIMARY KEY,
        username VARCHAR(50) NOT NULL,
        email VARCHAR(255) NOT NULL,
        CONSTRAINT uq_users_email UNIQUE (email) -- Ensures every email is unique
    );
    ```

### 4. `NOT NULL`
A `NOT NULL` constraint ensures that a column cannot have a `NULL` value. This means a value must be provided for that column when a new record is inserted or an existing record is updated.

*   **Purpose:** To enforce that a field must always contain a value.
*   **Example:**
    ```sql
    CREATE TABLE products (
        product_id INT PRIMARY KEY,
        product_name VARCHAR(100) NOT NULL, -- product_name cannot be empty
        price DECIMAL(10, 2) NOT NULL       -- price cannot be empty
    );
    ```

### 5. `DEFAULT`
The `DEFAULT` constraint is used to set a default value for a column. The default value will be added to all new records if no other value is specified.

*   **Purpose:** To provide a fallback value for a column when one isn't explicitly provided during an `INSERT` operation.
*   **Example:**
    ```sql
    CREATE TABLE users (
        id INT PRIMARY KEY,
        username VARCHAR(50) NOT NULL,
        registration_date DATE DEFAULT (CURRENT_DATE) -- Defaults to the current date
    );
    ```

### 6. `CHECK`
A `CHECK` constraint is used to limit the value range that can be placed in a column. It ensures that all values in a column satisfy a specific condition.

*   **Key Properties:**
    *   The condition is defined with a boolean expression that must evaluate to `TRUE` or `UNKNOWN` (due to `NULL`).
    *   Historically, MySQL parsed `CHECK` constraints but did not enforce them. However, since **MySQL 8.0.16**, `CHECK` constraints are fully supported and enforced.
*   **Purpose:** To enforce business rules directly in the database, such as ensuring a price is positive or a gender is within a specific set of values.
*   **Example:**
    ```sql
    CREATE TABLE products (
        product_id INT PRIMARY KEY,
        product_name VARCHAR(100) NOT NULL,
        price DECIMAL(10, 2) NOT NULL,
        CONSTRAINT chk_products_price CHECK (price > 0) -- Ensures price is always positive
    );
    ```
These constraints are the building blocks for creating a robust, reliable, and well-structured database.