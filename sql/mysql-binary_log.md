

```bash

```




```sql
-- check if **binary logs** are enabled
SHOW VARIABLES LIKE 'log_bin';
-- If log_bin: `ON`, binary logging is enabled.
-- If log_bin `OFF`, binary logging is disabled.

-- check the name of the binary log file (if enabled)
SHOW MASTER STATUS;
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

---

## **Types of Binary Log Events**

- **Statement-Based Logging (SBL):** Logs the actual SQL statements.
- **Row-Based Logging (RBL):** Logs the actual changes made to each row.
- **Mixed:** MySQL automatically chooses between statement and row-based logging.

You can set the format with:
```sql
SET GLOBAL binlog_format = 'ROW'; -- or 'STATEMENT' or 'MIXED'
```

---

## **How to Enable the Binary Log**

Add the following lines to your `my.cnf` or `my.ini` configuration file under the `[mysqld]` section:

```ini
[mysqld]
log-bin=mysql-bin
server-id=1
```

- Restart MySQL after making changes.

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