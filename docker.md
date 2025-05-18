## commands
```bash
### installation (https://docs.docker.com/engine/install/)
```bash
docker version
docker info
service docker start
service docker status
docker run hello-world

### image-management
`docker image ls`  # list all docker-image commands
## create docker image using `Dockerfile` (https://docs.docker.com/engine/reference/builder)
```bash
docker build -f <path-of-Dockerfile> -t <name:tag> . # don't forget "." at the end
docker images ls # list all images
docker image rm <image-id>

### container management
## create container
docker inspect <container-id>
docker inspect <container-id> | grep project.working  # get docker-compose file which started the container
docker container run -d -p 4306:3306 --name db -e MYSQL_RANDOM_ROOT_PASSWORD=yes mysql
# here `mysql` is name of image, `db` will be the name of newly-created container
# -e  == --env, -d == --detach (run container in background)
# -p == --publish, here `3306` is the port inside docker-container, `4306` is port from where we can access 3306
# environment variables will be shown in logs whenever you start the container
docker container run -it <image-id> bash # interact with conatiner using bash
docker container exec -it <container-name> bash
# run == create new container, exec == interact with already running container
# keep CMD = ["bash"] on last line of Dockerfile, if you want access image using bash
docker containr ls # list all running containers
docker containr ls -a # list all containers
docker container stop <container-id> <container-id2>
docker container start <container-id>
docker container rm <container-id1> <container-id2> # remove stopped containers
docker container rename curr_name new_name
docker container stats  # check cpu and memory usage of all running containers
docker container insepct <container-name>  # check the configuration of the container
docker container logs <container-name>
docker container top <container-name> # list processes running by the container

### docker volume
docker volume create my-vol
docker volume ls
docker volume inspect my-vol
docker volume rm my-vol


### docker compose
docker compose up -d  # start containers mentioned in docker-compose.yml
docker compose logs 
docker compose -f ./main.yml up -d  # start containers mentioned given <any>.yml file
docker compose down # stop containers started through `up`
docker compose pause
docker compose unpause

# docker-network
docker network inspect <network-name>

# dockerhub
docker login -u <username>  # past Access-Token as password
docker push youngmahesh/node1
docker logout
```
## Examples
### Example-Dockerfile: nodejs
```bash
# nodejs app using offical nodejs image
FROM node:16

# Create and switch to app directory
WORKDIR /app

# docker uses cache of previuos build until it reaches to the command where files are changed, hence if we use npm install before copying all folders, it will reuse cache of previous `npm install` until package.json file is not changed
COPY package*.json ./
RUN npm install

# copy source code
COPY . .

EXPOSE 8080

# better to use ENTRYPOINT instead of CMD, if the command will always remain same, and there will be no additional
# paramaeters needed to pass in the command
CMD [ "node", "server.js"]
```
### Example-Dockerfile: ubuntu + nodejs
```bash
FROM ubuntu:20.04
# -y == response yes if prompted do you want to continue
RUN apt update && apt -y upgrade
RUN apt install -y curl
RUN curl -fsSL https://deb.nodesource.com/setup_lts.x | bash -
RUN apt install -y nodejs
RUN apt install -y build-essential

WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
EXPOSE 8080
CMD [ "node", "server.js"]
```
### Example-dockerignore
- `node_modules`
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

## Concepts
- There are primarily three sections in docker:
	1. Docker Images
	2. Docker Containers
	3. DockerHub
- Containers vs Images
	- Container is instance of image running as a process, you can run many containers using the same image
- We write code and create / build image of it locally, push image it DockerHub, pull it on production-server and run it to make website live
### files
1. `Dockerfile`: Define enviornment in which app-code will run
2. `.dockerignore`: same as `.gitignore` include, path of folders/files which will be not copied inside docker-image when docker execute `COPY . .` inside Dockerfile
3. `docker-compose.yml`:
- define multi-container Docker applications
- define your application's services, networks, and volumes in a single YAML file
- preserve volume data when containers are created
### docker workflow
- Create App -> Create Dockerfile -> Create docker-image using Dockerfile and app-code -> Run docker-image as container on a port -> Assign domains to exposed port of docker-container
### docker-networking
- by default docker-container is part of bridge-network, and two containers does not talk with each other
- we can make two docker-containers work with each other using
	1. `--link`
	2. `--network`: creating-custom-network and run two container on the same network
	
- ## Possible errors while working with docker
```bash
# problem
docker: permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Post "http://%2Fvar%2Frun%2Fdocker.sock/v1.24/containers/create": dial unix /var/run/docker.sock: connect: permission denied.
See 'docker run --help'.

# solution
sudo chmod 666 /var/run/docker.sock
```