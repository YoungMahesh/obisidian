```yml
services:
  mysql1:
    container_name: mysql1
    image: mysql:8.3.0
    environment:
      MYSQL_ROOT_PASSWORD: <random-password>
    ports:
      - 3307:3306
    volumes:
      - ./mysql1:/var/lib/mysql
```

### interact with mysql inside container
```bash
# Enter the container
# -it == interactive-mode
docker exec -it mysql_container bash

# list files/folders inside container
ls

# Exit the container
exit
```

### backup database
```bash
# 1. provide password in command
# docker exec -it <container-name> \
#   mysqldump --source-data=1 -u<username> -p<password> <database-name> > ./<backup-file-name>
# The --source-data option in mysqldump is used to record the binary log coordinates (file and position) in the dump file. 
#   This is crucial for point-in-time recovery and setting up replication.
docker exec -it mysql1 \
  mysqldump --source-data=1 -uroot -pMySecretPassword mydatabase > ./backup.sql

# 2. provide password through prompt
docker exec -it mysql1 \
  mysqldump --source-data=1 -uroot -p mydatabase > ./backup.sql
# paste password after above command
# ---
# now first line of backup.sql has `Enter password:` line, as prompt output was also saved
# verify data inside file using less
less ./backup.sql
# delete first line from backup.sql
sed -i '1d' ./backup.sql
# verify if we didn't missed anything
less ./backup.sql
```

### restore specific content of the database
- restore data lost due to specific query - [[mysql-binary_log]]

### restore whole database

```bash
# create new database
docker exec -it mysql_container mysql -uroot -pMySecretPassword -e "CREATE DATABASE new_database;"

# execute backup.sql in new database
docker exec -i mysql_container mysql -uroot -pMySecretPassword new_database < /backup.sql
```

### delete database
```bash
# -p = prompts you to enter the MySQL user’s password.
# -e = Executes the SQL statement provided as a string which allows you to pass a SQL command directly from the command line, 
#   so you don’t have to enter the MySQL shell interactively.
docker exec -it mysql-container mysql -u root -p -e "DROP DATABASE mydatabase;"
```