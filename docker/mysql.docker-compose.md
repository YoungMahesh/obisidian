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
# mysqldump -u<username> -p<password> <database-name> > /<backup-file-name>
mysqldump -uroot -pMySecretPassword mydatabase > /backup.sql

# 3. Exit the container
exit

# 4. On the host, copy the backup to your current directory
docker cp mysql_container:/backup.sql .

# 5. remove backup file inside container
docker exec mysql_container rm /backup.sql
docker exec mysql_container ls # verify if file is removed
```

### restore database
```bash
# create new database
docker exec -it mysql_container mysql -uroot -pMySecretPassword -e "CREATE DATABASE new_database;"

# execute backup.sql in new database
docker exec -i mysql_container mysql -uroot -pMySecretPassword new_database < /backup.sql
```