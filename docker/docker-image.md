## commands
```bash
### image-management
docker image ls  # list all docker-image commands

## create docker image using `Dockerfile` (https://docs.docker.com/engine/reference/builder)
docker build -f <path-of-Dockerfile> -t <name:tag> . # don't forget "." at the end
docker images ls # list all images
docker image rm <image-id>
```
