#database/mysql 

### read
#database/mysql/select #database/mysql/join
```sql
-- read transactions rows
SELECT *
FROM transactions
where amount > 100      -- amount column from transaction-table
ORDER BY created_at ASC -- created_at column from transaction-table
LIMIT 20, 10;

-- get distinct values from table alongwith their count
SELECT column_name, COUNT(*) as count
FROM table_name
GROUP BY column_name
ORDER BY column_name;
-- without count
SELECT DISTINCT column_name
FROM table_name
ORDER BY column_name;

-- get distinct combination for columns - make, model from table  products_6
SELECT DISTINCT make, model 
FROM products_6
ORDER BY make, model;
SELECT make, model, COUNT(*) as count
FROM products_6
GROUP BY make, model
ORDER BY make, model;

-- -------------- innerjoin  ---------
-- An INNER JOIN returns only the rows where there is a match in both tables based on a specified column.
-- If rows do not have a matching value in both tables, they are excluded from the result.
-- This query returns items that have a matching category.
SELECT i.id, i.name, c.name AS category_name
FROM items i
INNER JOIN categories c ON i.category_id = c.id;

-- ------------- leftjoin -------------
-- A LEFT JOIN returns all rows from the left table and the matching rows from the right table.
-- If there is no match, the right table columns show NULL.
-- This returns all employees, with department names where available, otherwise NULL.
SELECT employees.employee_id, employees.employee_name, departments.department_name
FROM employees
LEFT JOIN departments ON employees.department_id = departments.department_id;

-- ------------- rightjoin -------------
-- A RIGHT JOIN returns all rows from the right table and matching rows from the left table.
-- If there is no match, the left table columns show NULL.
-- This returns every department and any matching employee names, NULL if no employees.
SELECT employees.employee_name, departments.department_name
FROM employees
RIGHT JOIN departments ON employees.department_id = departments.department_id;
```
### update, create, delete, count
```sql
-------------------------- update rows ------------------------------------

-- you cannot use 'table' during update; e.g. `update table ticket` is invalid
update ticket set status = 'approved-1' where status = 'verified';
update ticket set status = 'approved-2'; -- update all rows

-- convert all amounts in balance column to negative
UPDATE abc SET balance = -balance;

----------------------------- create rows --------------------------------------

insert into info1 (name, amount, expiry_at)
values ('task m1', 130.33, date_add(current_timestamp, interval 1 day)); -- expires after 1 day from current time

insert into info1(name, amount)
values
    ('row1', 10),
    ('row2', 20),
    ('row3', 30);

-------------------------- delete rows ------------------------------------

-- delete single row
delete from info1
where id = 3
limit 1;

delete from info1; -- delete all rows from table info1

delete from info where name is null;

--------------- circular depedency ----------------------
-- suppose info1 has a foreign key to info2.id
-- and info2 has a foreign key to info1.id
-- This creates a circular dependency that prevents you from deleting records from either table directly.
-- To solve this problem, we need to temporarily disable foreign key checks, delete the data, and then re-enable the checks.
-- Temporarily disable foreign key checks
set foreign_key_checks=0;
-- Delete data from both tables
delete from info1;
delete from info2;
-- Re-enable foreign key checks
set foreign_key_checks=1;

--------------- count rows ----------------
SELECT COUNT(*) AS total_count
FROM transactions;
```

### get rows with duplicate timestamps
```sql
SELECT *
FROM donor_transaction
WHERE created_at IN (
    SELECT created_at
    FROM donor_transaction
    GROUP BY created_at
    HAVING COUNT(*) > 1
)
ORDER BY created_at;
```


### sum of all values in a column
```sql
select sum(amount) as total_info1_amt from info1;
```