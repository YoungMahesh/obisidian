

```sql
-- check if **binary logs** are enabled
SHOW VARIABLES LIKE 'log_bin';
-- If log_bin: `ON`, binary logging is enabled.
-- If log_bin `OFF`, binary logging is disabled.

-- check the name of the binary log file (if enabled)
SHOW MASTER STATUS;

-- show available binary logs
SHOW BINARY LOGS;

-- check the binary log event types in MySQL
SHOW BINLOG EVENTS IN 'your-binlog-file';
-- example: SHOW BINLOG EVENTS IN 'binlog.000247';
```

## Description

The **binary log** is a set of log files that record all changes to the database (such as `INSERT`, `UPDATE`, `DELETE`, `CREATE`, etc.), but **not** `SELECT` statements or other queries that do not modify data.


- You **cannot** enable or disable binary logging for only a specific database. It is either on or off for the whole server.
- The binlog records **committed transactions** only.
- If a transaction is rolled back, it is **not** written to the binlog.
---

## **Key Purposes of the Binary Log**

1. **Replication:**  
   The binlog is used to replicate changes from a primary (source) server to one or more replicas (slaves).

2. **Point-in-Time Recovery:**  
   You can restore a backup and then replay the binlog to recover the database up to a specific point in time.

---

## **How Does the Binary Log Work?**

- Every time a data-changing statement is executed, MySQL writes an event to the binary log.
- The log is stored in a binary format (not human-readable).
- The log is split into multiple files, typically named like `mysql-bin.000001`, `mysql-bin.000002`, etc.

## Binary Log Events

**Binary log events** in MySQL are records written to the binary log (`binlog`) that describe changes made to the database. 

The binary log is a crucial component for **replication**, **point-in-time recovery**, and **auditing**. Each event in the binary log represents a specific action or change, such as a data modification or a statement execution.

### Key Points about Binary Log Events

- **Purpose:**  
  They record all changes to the database (data changes and some administrative operations) so that these changes can be replicated to a slave server or used for recovery.

- **Format:**  
  Events are stored in a binary format for efficiency.

- **Types:**  
  The type of event depends on the binary log format (`STATEMENT`, `ROW`, or `MIXED`).

### Common Types of Binary Log Events

Here are some of the most important binary log event types:

| Event Type                 | Description                                                             |
| -------------------------- | ----------------------------------------------------------------------- |
| `Query_event`              | Records a SQL statement (used in STATEMENT or MIXED format).            |
| `Write_rows_event`         | Records row insertions (used in ROW or MIXED format).                   |
| `Update_rows_event`        | Records row updates (used in ROW or MIXED format).                      |
| `Delete_rows_event`        | Records row deletions (used in ROW or MIXED format).                    |
| `Table_map_event`          | Maps a table ID to a table definition (used in ROW or MIXED format).    |
| `Rotate_event`             | Indicates that the server has started writing to a new binary log file. |
| `Format_description_event` | Describes the format of the binary log file.                            |
| `Xid_event`                | Marks the commit of a transaction.                                      |
| `Begin_load_query_event`   | Used for loading data (e.g., `LOAD DATA INFILE`).                       |
| `Stop_event`               | Marks the end of the binary log file.                                   |

### How Are They Used?

- **Replication:**  
  Replica servers read binary log events from the primary server to apply the same changes and stay in sync.

- **Point-in-Time Recovery:**  
  You can replay binary log events to restore a database to a specific point in time after a backup.

- **Auditing:**  
  You can analyze binary log events to see what changes were made and by whom.

### Viewing Binary Log Events

You can view binary log events using the `mysqlbinlog` utility or the SQL command:

```sql
SHOW BINLOG EVENTS IN 'mysql-bin.000001';
```

---

**In summary:**  
Binary log events are the fundamental units of change recorded in MySQL’s binary log, enabling replication, recovery, and auditing by capturing every significant action performed on the database.

---

## Types of Binary Log Events

- **Statement-Based Logging (SBL):** Logs the actual SQL statements.
- **Row-Based Logging (RBL):** Logs the actual changes made to each row.
- **Mixed:** MySQL automatically chooses between statement and row-based logging.

```sql
-- check binary log format currently in use by MySQL server
SHOW VARIABLES LIKE 'binlog_format';

-- set binary log format
SET GLOBAL binlog_format = 'ROW'; -- or 'STATEMENT' or 'MIXED'
```

---


## **How to View the Binary Log**

Since the binlog is in binary format, use the `mysqlbinlog` utility to read it:

```bash
mysqlbinlog mysql-bin.000001
```

You can also filter by time or position for point-in-time recovery.

---

## **Binary Log Maintenance**

- **Log Rotation:**  
  MySQL automatically rotates the binlog files. You can control retention with:
  ```ini
  expire_logs_days = 7
```
  (Keeps logs for 7 days.)

- **Manual Purge:**  
  ```sql
  PURGE BINARY LOGS TO 'mysql-bin.000010';
  ```
  or
  ```sql
  PURGE BINARY LOGS BEFORE '2025-06-01 00:00:00';
  ```


---

- Binary logs are by default disabled in MySQL 5.5/5.6/5.7, and enabled in MySQL 8.0