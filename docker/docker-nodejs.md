
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