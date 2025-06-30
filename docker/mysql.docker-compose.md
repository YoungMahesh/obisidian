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


### backup database
```bash
# 1. Enter the container
docker exec -it mysql_container bash

# 2. Inside the container, create the backup
# mysqldump --master-data=1 -u<username> -p<password> <database-name> > /<backup-file-name>
# The --master-data option in mysqldump is used to record the binary log coordinates (file and position) in the dump file. 
#   This is crucial for point-in-time recovery and setting up replication.
mysqldump --master-data=1 -uroot -pMySecretPassword mydatabase > /backup.sql

# 3. Exit the container
exit

# 4. On the host, copy the backup to your current directory
docker cp mysql_container:/backup.sql .

# 5. remove backup file inside container
docker exec mysql_container rm /backup.sql
docker exec mysql_container ls # verify if file is removed
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