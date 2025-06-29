```yml
services:
  phpmyadmin1:
    container_name: phpmyadmin1
    image: phpmyadmin:5.2.1
    ports:
      - 3308:80
    environment:
      - PMA_HOST=mysql1 # ip-address of database
      - PMA_PORT=3306  # port of database
      # - PMA_ARBITRARY=1 # allow user to connect arbitrary server by providing "Server" field during login
      - UPLOAD_LIMIT=100M # override the default value (2048KB), during import of .sql file
```