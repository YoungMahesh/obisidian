
[[docker-nodejs]]
[[traefik.docker-compose]]
[[mysql.docker-compose]]
[[phpmyadmin.docker-compose]]
## commands

### container 
```bash
## inspect container
docker inspect <container-id>
docker inspect <container-id> | grep project.working  # get docker-compose file which started the container

## create container
docker container run -d -p 4306:3306 --name db -e MYSQL_RANDOM_ROOT_PASSWORD=yes mysql
# here `mysql` is name of image, `db` will be the name of newly-created container
# -e  == --env, -d == --detach (run container in background)
# -p == --publish, here `3306` is the port inside docker-container, `4306` is port from where we can access 3306
# environment variables will be shown in logs whenever you start the container

# interact with container file-system
docker container run -it <image-id> bash # interact with conatiner using bash
docker container exec -it <container-name> bash
# run == create new container, exec == interact with already running container
# keep CMD = ["bash"] on last line of Dockerfile, if you want access image using bash

# manage containers
docker containr ls # list all running containers
docker container ls --format "table {{.ID}}\t{{.Names}}\t{{.Image}}"
docker containr ls -a # list all containers
docker container stop <container-id> <container-id2>
docker container start <container-id>
docker container rm <container-id1> <container-id2> # remove stopped containers
docker container rename curr_name new_name
docker container stats  # check cpu and memory usage of all running containers
docker container insepct <container-name>  # check the configuration of the container
docker container logs <container-name>
docker container top <container-name> # list processes running by the container
```

### compose
```bash
### docker compose
docker compose up -d  # start containers mentioned in docker-compose.yml
docker compose logs 
docker compose -f ./main.yml up -d  # start containers mentioned given <any>.yml file
docker compose down # stop containers started through `up`
docker compose pause
docker compose unpause
```

## Examples

```yml
services:
  service1:
    container_name: xyz
    # restart policy
    # no: Never attempt to restart the container if it stops or crashes
    # always: Always attempt to restart the container if it stops for any reason
    # on-failure: Restart the container only if it stops with an error code (non-zero code)
    # unless-stopped: Always restart the container unless it is manually stopped
    restart: unless-stopped
```

### Example-dockerignore

```dockerignore
node_modules
```
### Example Docker-compose file
```bash
# docker-compose.yml

version: "3.7"
services:
  currency-exchange:
    image: in28min/currency-exchange:0.0.1-RELEASE
    ports:
      - "8000:8000"
    restart: always
    networks:
      - currency-compose-network

  currency-conversion:
    image: in28min/currency-conversion:0.0.1-RELEASE
    ports:
      - "8100:8100"
    restart: always
    environment:
      CURRENCY_EXCHANGE_SERVICE_HOST: http://currency-exchange
    depends_on: # tells docker to start currency-exchange service first
      - currency-exchange
    networks:
      - currency-compose-network

# Networks to be created to facilitate communication between containers
networks:
  currency-compose-network:
```