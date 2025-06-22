# examples

```sql
-- postgres have case insensitive sql query syntax (including column-names)

create type eye_color as enum ('brown', 'blue', 'hazel', 'gray');
create table model (
    -- serial = auto-incrementing intenger column
    id serial primary key,
    person_id integer not null references person(id),
    -- in postgres, text is recommended for storing string most use cases where you don't need a strict length limit
    description text,
    name varchar(255) not null,
    age integer not null,
    eye_color eye_color NOT NULL default 'brown',
    bald boolean not null,
    createdAt timestamp not null default now(),
    updatedAt timestamp not null default now()

    pack_id integer not null,
    foreign key (pack_id) references pack(id) on delete cascade
);

alter table model
rename column updatedat to updated_at;
```

### mysql supports by postgres does not

- grouped statments (rename): PostgreSQL requires separate ALTER TABLE statements for each column you want to rename, it does not support:
  ```sql
  -- not supported in postgres
  alter table model
  rename column createdat to created_at,
  rename column updatedat to updated_at;

  -- supported in postgres: multiple `add column` statements
  ```
- `after` clause: to define position of column in table
- word `user` without quotes: user is reserved keyword in postgres, you need use `"user"` instead of `user`
- `timestamp on update`: in postgres, you need to update updated_at column during update statement

### types

- Built-in Primitive Types:

  - INTEGER: Whole numbers
  - SERIAL: Auto-incrementing integer
  - BIGINT: Large integer
  - SMALLINT: Small integer
  - NUMERIC/DECIMAL: Precise decimal numbers
  - REAL/FLOAT: Floating-point numbers
  - TEXT: Variable-length string
  - VARCHAR: Variable-length character string
  - CHAR: Fixed-length character string
  - BOOLEAN: True/False values
  - DATE: Date values
  - TIMESTAMP: Date and time
  - INTERVAL: Time spans

- Enumerated Types (ENUM):

  - User-defined types with a fixed set of values
  - Restricts column to only allow predefined values
  - Example: `CREATE TYPE eye_color AS ENUM ('brown', 'blue', 'hazel', 'gray');`

- Array Types:

  - Can create arrays of any existing type
  - Example: `TEXT[], INTEGER[]`

- Composite Types:

  - Similar to structs in other languages
  - Can group multiple fields together

  ```sql
  CREATE TYPE address AS (
      street TEXT,
      city TEXT,
      zip_code VARCHAR(10)
  );
  ```

- Range Types:

  - Represent a range of values
  - Examples: int4range, tsrange

- JSON Types:

  - JSON: Strict JSON validation
  - JSONB: Binary JSON with indexing support

- Network Address Types:

  - INET: IP addresses
  - CIDR: Network addresses

- Geometric Types:

  - POINT: Geometric point
  - LINE: Geometric line
  - POLYGON: Geometric polygon

- Custom Domain Types:
  - User-defined types based on existing types with additional constraints
  ```sql
  CREATE DOMAIN positive_integer AS INTEGER
  CHECK (VALUE > 0);
  ```

### run postgresql with [docker container](https://hub.docker.com/_/postgres)

```bash
#------------------- docker container configuration for these docs -------------------
# container_name: postgres
# user: postgres

#--------------------- outside postgres-docker-container -----------------------------------
docker exec -it postgres bash  # go inside postgresql container, 'postgres' is container-name
docker cp postgres:/backups/backup-name.dump .  # copy dump-file from container to outside container
docker cp ./backups postgres:/backups/   # copy data from outside container to inside containe

# -------------------- install vector extension (for ai) -------------
docker exec -it <postgres-container-name> sh -c apk add --no-cache postgresql-contrib-vector

#--------------------- inside postgres-docker-container ----------------------------------------
# backup and restore postgresql
# https://www.postgresql.org/docs/15/app-pgdump.html
mkdir backups && cd backups  # create folder to store backups
pg_dump -Fc db-name > db.dump # pg_dump is pre-installed on postgres docker-image
# -Fc => -F=format, c=custom
pg_restore -x -U postgres -d mydb /mydb.dump  # -U postgres == user named `postgres` will be the owner of database
# -d mydb /mydb.dump   ==  restore dump file in database named `mydb`
# -x == --no-privileges, avoids errors due to differennt in database_owner @backup_container and @restore_container
pg_restore -x -d 'postgres://user1:xyz@example.com/timers' timers_5nov.dump # restore to remote_database

# ----------------- inside postgresql of postgres-docker-container -------------------------------
psql -U postgres # connect to sql-cli of container with user `postgres`
# restore database from text dump file
# if database (here `mydb`) does not exist, create it before restoring dump file
psql -U postgres -d mydb -f mydb.dump
# -U specifies the username of the PostgreSQL user that owns the database.
# -d specifies the name of the database to restore the dump file to.
# -f specifies the path to the dump file.
psql \du  # list users/roles in current-postgres

# connect with remote database
psql -h containers-us-west-96.railway.app -p 6447 -U postgres -d database1 --set=sslmode=require
# -h : The hostname of the remote PostgreSQL server.
# -p : The port number of the remote PostgreSQL server.
# -U : The username that you want to use to connect to the remote PostgreSQL server.
# -d : database name
# --set=sslmode=require: optional, need to used when remote_database requires ssl-connection
# you will get prompt for password

```

### backup and restore

- sometimes restore using defaults commands can give issues when owner-name, external schemas(schemas not related to database) are different
- in this case, better way is to backup and restore only tables instead of whole is database using pgAdmin
- backup data using pgAdmin
  1. click _backup_ form right-click of `public` from `Object Explorer -> Servers -> server-name -> Databases -> Schemas -> public`
  2. provide file-name
  3. click `Backup`
- restore data using pgAdmin
  1. click _restore_ from right-click of `public` of `Object Explorer -> Servers -> server-name -> Databases -> Schemas -> public`
  2. from the restore-popup-table: 1) select backup-file 2) enable `Data Options -> Do not save -> Owner`
  3. Click `Restore`
