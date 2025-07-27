#database/mysql 
## Point-in-Time Recovery (PITR)

The following tutorial guides you through the process of performing a point-in-time recovery of a MySQL database. The environment for which these commands are created includes:

*   MySQL server running in a Docker container
*   Binary logs enabled with the type set to 'ROW' (enabled by default in the MySQL Docker container)
*   A MySQL database backup file (`backup.sql`) containing binary log coordinates (created using `--source-data=2` with `mysqldump`)
*   The old database (with data loss) and the new database (for recovery) are on the same MySQL server

### Process

The point-in-time recovery process involves the following steps:
#### Step 1: Copy the Binary Log File
Copy the binary log file mentioned in `backup.sql`. The file name and position are specified in the line starting with `-- CHANGE REPLICATION SOURCE TO SOURCE_LOG_FILE`.
e.g.` -- CHANGE REPLICATION SOURCE TO SOURCE_LOG_FILE='binlog.000248', SOURCE_LOG_POS=2140;`

```bash
docker cp mysql1:/var/lib/mysql/binlog.000248 .
```

If the current binary log file is different from the one in the backup file, you may need to copy additional binary log files. To determine the latest binary log file, execute the SQL query `SHOW MASTER STATUS;` in MySQL.

#### Step 2: Create a New Database and Restore Backup Data
This step is performed after copying the binary log file to avoid including unnecessary additional logs of database-creation, row-insertions during data-restoration.

```bash
docker exec -it mysql_container mysql -uroot -pMySecretPassword -e "CREATE DATABASE new_database;"
docker exec -i mysql_container mysql -uroot -pMySecretPassword new_database < /backup.sql
```

#### Step 3: Determine Start and End Positions
Determine the start and end positions for the binary log file.

*   **Start Position**: Extracted from the `backup.sql` file, e.g., `2140` in `-- CHANGE REPLICATION SOURCE TO SOURCE_LOG_FILE='binlog.000248', SOURCE_LOG_POS=2140;`
*   **End Position**: Found by decoding the binary log file using `mysqlbinlog` and browsing through the output to identify the position just before the data loss query. e.g., 2140 in `COMMIT/*!*/; \n #at 2140`

```bash
# --database = name of the database whose logs we want to decode
# ignore warning: `you should use the options --exclude-gtids or --include-gtids` as it is not relevant in our case
mysqlbinlog --database=college2 --base64-output=DECODE-ROWS -vv binlog.000248 > ./decoded2.txt
# decoded binary file can be very long, use #less to browse it
```


#### Step 4: Create `apply.sql` Using `mysqlbinlog`
Use `mysqlbinlog` to create `apply.sql` with the specified start and end positions, and rewrite the database name.

```bash
# old-database: database which we backed up and lost data
# new-database: database which we crated, dumped backup.sql and will 
# mysqlbinlog --start-position=START_POS --stop-position=STOP_POS \
#   --rewrite-db=<old-database-name>-><new-database-name>
#   /path/to/<binlog-file> > apply.sql
mysqlbinlog \
  --start-position=2140 --stop-position=2455 \
  --rewrite-db='college2->college3' \
  binlog.000248 > apply.sql
```

#### Step 5: Apply Changes to the New Database
Apply the changes from `apply.sql` to the new database.

```bash
# docker exec -i <mysql-container-name> mysql -u<username> -p<password> \
#   <database-name> < apply.sql
docker exec -i mysql-container \
  mysql -uuser -ppassword college3 < apply.sql
```

---

### Supplementary Information

*   To install `mysqlbinlog` on Ubuntu, run: `sudo apt install mysql-server-core-8.0`
*   Useful SQL queries:
    *   List all binary log files on the server: `SHOW BINARY LOGS;`
    *   List the current binary log file and position: `SHOW MASTER STATUS;`
    *   Check if binary logs are enabled: `SHOW VARIABLES LIKE 'log_bin';`
*   To check binary log event types in MySQL, use: `SHOW BINLOG EVENTS IN '<binlog-file>';`
	- Output of this query does not show actual query, timestamp (if event-type = 'ROW')


---

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