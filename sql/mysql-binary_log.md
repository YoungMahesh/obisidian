### point-in-time recovery (PITR)
```bash
# you should have:
# 1) binary logs enabled with type of binary logs = 'ROW'; 
#   by default mysql-server have this
# 2) mysql backup-file with binary-log coordinates
#   global-search #backup for this

# 1. copy binary-log file mentioned in backup.sql
# e.g. -- CHANGE REPLICATION SOURCE TO SOURCE_LOG_FILE='binlog.000248', SOURCE_LOG_POS=2140;
#   in above line of backup.sql binlog.000248 is the binlog file we need to copy
# docker cp <mysql-container-name>:/var/lib/mysql/<binlog-file> .
docker cp mysql1:/var/lib/mysql/binlog.000248 .
# if our current binary-log file is different (must have higher number) from coordinates in backup-file, then we need to copy and use more binary-log files
#   starting id of binary file from id in backup.sql to shown in output of current binary-file
#   e.g. 000248 is id of above binary-file
#   execute sql query `SHOW MASTER STATUS;` in mysql to get latest binary-file id

# 2. create new database, add backup-data inside it
# we are doing this after copying binery-log file, as if we did it before then will also contain logs of:
#   1) database-creation 2) new rows created during data-restoration
#   we don't need these extra logs which can be huge in size
docker exec -it mysql_container mysql -uroot -pMySecretPassword -e "CREATE DATABASE new_database;"
docker exec -i mysql_container mysql -uroot -pMySecretPassword new_database < /backup.sql

# 3. get start-position and end-position 
# A. get start-position
#   e.g. in `-- CHANGE REPLICATION SOURCE TO SOURCE_LOG_FILE='binlog.000248', SOURCE_LOG_POS=2140;` at top of backup.sql
#   our start_position at 2140 (considering bilog-file remains same - binlog.000248)
# B. get end-position
#   start browsing through decoded.txt from start-position (e.g. 2140), you will see something like
#     #250701 16:22:48 server id 1  end_log_pos 2140 CRC32 0x8fb81c7e 	Xid = 826
#     COMMIT/*!*/;
#     #at 2140
#   continue until you are just before data-loss query-statement, note down position which will act as stop_position (e.g. COMMIT/*!*/; at 2455)
# --database = name of the database whose logs we want to decode
#   ignore warning: `you should use the options --exclude-gtids or --include-gtids` as it is not relevant in our case
mysqlbinlog --database=college2 --base64-output=DECODE-ROWS -vv binlog.000248 > ./decoded2.txt
# decoded binary file can be very long, use #less to browse it

# 4. decide start_position and stop_position in binary-log, use them to create apply.sql
# old-database: database which we backed up and lost data
# new-database: database which we crated, dumped backup.sql and will 
#   execute new queries from start_position to stop_position to restore 
#   lost-data while retaining essential changes after backup.sql creation
# mysqlbinlog --start-position=START_POS --stop-position=STOP_POS \
#   --rewrite-db=<old-database-name>-><new-database-name>
#   /path/to/<binlog-file> > apply.sql
mysqlbinlog \
  --start-position=2140 --stop-position=2455 \
  --rewrite-db='college2->college3' \
  binlog.000248 > apply.sql

# 5. apply changes to new database
# docker exec -i <mysql-container-name> mysql -u<username> -p<password> \
#   <database-name> < apply.sql
docker exec -i mysql-container \
  mysql -uuser -ppassword college3 < apply.sql
```

```sql
-- check if **binary logs** are enabled
SHOW VARIABLES LIKE 'log_bin';
-- If log_bin: `ON`, binary logging is enabled.
-- If log_bin `OFF`, binary logging is disabled.

-- Displays the current status of the binary log on the master server, including the name and position of the current binary log file.
SHOW MASTER STATUS;

-- Lists all binary log files that exist on the server.
SHOW BINARY LOGS;

-- check the binary log event types in MySQL
-- does not show actual timestamp
-- does not show actual query (if event-type is 'ROW')
SHOW BINLOG EVENTS IN '<binlog-file>';
-- example: SHOW BINLOG EVENTS IN 'binlog.000247';

-- use mysqlbinlog to to get timestamp and actual queries from binlog events
-- for ubuntu, install mysql-server-core to install mysqlbinlog
sudo apt install mysql-server-core-8.0
mysqlbinlog --version
docker cp mysql1:/var/lib/mysql/<binlog-file> .
mysqlbinlog --base64-output=DECODE-ROWS -vv <binlog-file>
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

- **Sequential Nature:**  
  Each event in the binary log starts immediately after the previous event ends. The `Position` of the next event is equal to the `End_log_pos` of the previous event.
- **No Gaps:**  
  There are no gaps between events; the positions increase monotonically as new events are written.
- **Byte Offsets:**  
  Positions are measured in bytes from the beginning of the binary log file.

### Example

Suppose you run:

```sql
SHOW BINLOG EVENTS IN 'mysql-bin.000003';
```

You might see:

| Log_name         | Pos | Event_type  | End_log_pos | Info |
| ---------------- | --- | ----------- | ----------- | ---- |
| mysql-bin.000003 | 4   | Format_desc | 123         | ...  |
| mysql-bin.000003 | 123 | Query       | 200         | ...  |
| mysql-bin.000003 | 200 | Xid         | 230         | ...  |

- The first event starts at position 4 and ends at 123.
- The next event starts at 123 and ends at 200.
- The next event starts at 200 and ends at 230.

**This shows that positions are sequential and contiguous.**

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


### **Statement-Based Replication (SBR)**

**How it works:**  
Logs the actual SQL statements executed on the master.

#### **Pros**
- **Smaller binary logs:**  
  Only the SQL statements are logged, so logs are usually smaller.
- **Easier to read/audit:**  
  You can see the exact SQL that was executed.
- **Less disk I/O:**  
  Less data written to the binary log, which can mean less disk usage and network traffic.
- **Good for simple, deterministic queries:**  
  Works well when queries always produce the same result.

#### **Cons**
- **Non-deterministic statements:**  
  Statements like `NOW()`, `UUID()`, or `RAND()` may produce different results on replicas.
- **Side effects:**  
  Statements that depend on the current state (e.g., `UPDATE ... LIMIT 1`) may not replicate identically.
- **Triggers and stored procedures:**  
  May behave differently on replicas if they use non-deterministic logic.
- **Complex statements:**  
  Some complex or bulk operations may not replicate correctly.


### **Row-Based Replication (RBR)**

**How it works:**  
Logs the actual changes made to each row (before and after values), not the SQL statement.

#### **Pros**
- **Always deterministic:**  
  Replicas apply the exact same row changes, so results are always consistent.
- **Handles all statements:**  
  Even non-deterministic or complex statements replicate correctly.
- **Safer for triggers and stored procedures:**  
  Since only row changes are logged, side effects are minimized.
- **Better for some workloads:**  
  Especially for applications with many non-deterministic or bulk operations.

#### **Cons**
- **Larger binary logs:**  
  Every row change is logged, which can make logs much larger, especially for bulk operations.
- **Harder to audit:**  
  You see only the row changes, not the original SQL, making it harder to understand what was executed.
- **More disk I/O:**  
  More data written to the binary log, which can impact performance and network usage.
- **Difficult to reconstruct intent:**  
  You can’t easily see the business logic or intent behind the changes.

---

### **Summary Table**

| Feature/Aspect          | Statement-Based (SBR) | Row-Based (RBR)             |
| ----------------------- | --------------------- | --------------------------- |
| **Log size**            | Smaller               | Larger                      |
| **Auditability**        | Easy (see SQL)        | Hard (see only row changes) |
| **Determinism**         | Not always            | Always                      |
| **Handles all queries** | No (issues with some) | Yes                         |
| **Performance**         | Less I/O, faster      | More I/O, can be slower     |
| **Bulk operations**     | Efficient             | Can generate huge logs      |
| **Triggers/Procedures** | May cause issues      | Safer                       |
| **Non-deterministic**   | May cause issues      | Safe                        |


**In summary:**  
- **SBR** is more readable and efficient, but less reliable for complex or non-deterministic operations.
- **RBR** is more reliable and consistent, but produces larger logs and is harder to audit.

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