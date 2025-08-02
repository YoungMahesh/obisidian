#database/mysql 
## `.csv` to MySQL

- method 2 and 3 are unreliable, if `.csv` file is big, number of rows in csv-file > rows created in database

### method 1

- use Jupiter-notebook with pandas library in python

### method 2 (fast) - bash

```bash
# create a new table xyz with same table schema of existing table abc
create table <new-table-name> like <existing-table-name>;

# verify - column-count in csv file must be same as column-count / schema in mysql
describe <table_name>;

# check exisiting files in docker-container
docker exec <container_name_or_id> ls <path_inside_container>

# remove unwanted files
docker exec <container_name_or_id> rm <path_to_file_inside_container>

# only specific paths in container are accessible to mysql cmd, one of them is `/var/lib/mysql-files`, hence we will copy our file in this location
docker cp ./p1.csv <container-name>:/var/lib/mysql-files

# go to mysql command-line in container
docker exec -it <container-name> mysql -u root -p

use <database-name>;
show tables;
select count(*) from <table-name>;

# ----------- import csv --------------
# headers of csv, are column names in table
# ignore first row if it has headers
LOAD DATA INFILE '/var/lib/mysql-files/p1.csv'
INTO TABLE xyz
CHARACTER SET utf8mb4
FIELDS TERMINATED BY ','
# use 'ENCLOSED BY' if your column values are wrapped by "", else omit it
# e.g. use 'ENCLOSED BY' for: "1","John, Doe","New York"
#      do not use for: 1,John Doe,New York
# use 'OPTIONALLY ENCLOSED BY' if values are enclosed by " inconsistently
OPTIONALLY ENCLOSED BY '"'
# removed: LINES TERMINATED BY '\n'
#   as it gave `ERROR 1406 (22001): Data too long for column <column-name>` for one csv file
LINES TERMINATED BY '\r\n'
IGNORE 1 ROWS;


# ----------- import sql ------------
source /var/lib/mysql-files/p3.sql;

```

### method 3 (slow) - phpmyadmin

- open table in phpmyadmin ⇒ click import ⇒ choose-file ⇒ partial import (put 1 if csv have header) ⇒ click import
