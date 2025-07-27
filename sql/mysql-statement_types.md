#database/mysql

### DML (Data Manipulation Language)
- used to manipulate data stored in database tables
- do not change structure or schema of the database
- can be wrapped in transactions (`START TRANSACTION`, `COMMIT`, `ROLLABACK` )
- SELECT, INSERT, UPDATE, DELETE, CALL, EXPLAIN, LOCK TABLES, UNLOCK TABLES

### DDL (Data Definition Language)
- used to define, modify or remove structure of database objects (table, schema, index, etc)
- DDL statements are not transactional
- CREATE TABLE, ALTER TABLE, DROP TABLE, CREATE INDEX, DROP INDEX, CREATE DATABASE, DROP DATABASE, TRUNCATE TABLE, RENAME TABLE, CREATE VIEW, DROP VIEW

### TCL (Transaction Control Language)
- START TRANSACTION, COMMIT, ROLLBACK — control transactions.

### DCL (Data Control Language)
- GRANT, REVOKE (for permissions) 

