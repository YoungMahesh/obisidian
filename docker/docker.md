[[docker-container,compose]]
[[docker-image]]
## commands
```bash
#docker
### installation (https://docs.docker.com/engine/install/)
docker version
docker info
service docker start
service docker status
docker run hello-world
# remove unused data in docker
# ALERT: verify no important container is currently stopped, all are running
docker system prune -h
docker system prune

### docker volume
docker volume create my-vol
docker volume ls
docker volume inspect my-vol
docker volume rm my-vol

# docker-network
docker network inspect <network-name>

# dockerhub
docker login -u <username>  # past Access-Token as password
docker push youngmahesh/node1
docker logout
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