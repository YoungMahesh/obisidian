- example file: ./traefik.docker-compose.yml

# Errors

### Certificate Renewal for domain which no longer exists

- delete domain-entry associated with removed domain from acme.json (domain-certificate file) file
  - e.g. if `xyz.com | abc.com` were defined previously in docker-compose file, abc.com is removed but xyz.com is still in acme.json, then remove xyz.com from json file

# Theory

## [Concepts](https://doc.traefik.io/traefik/getting-started/concepts/)

- flow of request

  1. EntryPoints: define the port which will receive the packets, and whether listen to TCP or UDP
  2. Routers: connecting incoming requests to the services that can handle them
  3. Middlewares: attached to the routers, modify the requests or responses before they are sent to services
  4. Services: configuring how to reach the actual services
  5. Server/Application

- Traefik is a edge router: a network device or service which sits at the boundary (or 'edge') between different networks, specifically between
  internal infrastructure and external networks like the internet
- have native integration with AWS, Kubernetes, Docker, etc

## how

- traefik have static (startup time) and dynamic (while running) configuration

### static configuration

There are 3 different, mutually exclusive (e.g. you can use only one at a time), ways to define static configuration
options in traefik:

1. configuration file (yaml or toml)

- when traefik starts, it searches for a file named traefik.toml or traefik.yaml or traefik.yml in `/etc/traefik`
  directory

2. command-line arguments

- you can define these in docker-compose file

```yml
services:
  traefik:
    command:
      - "--api.insecure=true"
      - "--entrypoints.web.address=:81"
```

3. environment variables

- can be define in docker-compose file

  ```yml
  services:
    traefik:
      environment:
        - TRAEFIK_API_INSECURE=true
        - TRAEFIK_PROVIDERS_DOCKER=true
  ```

### dynamic configuration

- Providers are the configuration sources that dynamically inform traefik about the infrastructure, services, and routing rules

- [Traefik providers](https://doc.traefik.io/traefik/providers/overview/)

  - The providers are infrastructure components, whether orchestrators, container engines, cloud providers, or key-value stores.
  - Four catcategories of providers:
    1. Label-based: each deployed container has a set of labels attached to it
    2. Key-Value-based: each deployed container updates a key-value store with relevant information
    3. Annotation-based: a separate object, with annotations, defines the characteristics of the container
    4. File-based: uses files to define configuration

## why

- many of reverse proxies but none were dynamic
- e.g. traefik automatically detect new container, creates appropriate routing rules, domain setup just by looking at labels on container
- microservices are dynamic in natures (they starts and shut-down very frequently) but much of configuration is static means you need
  to update your reverse-proxy configuration separately whenever services are started or stopped
- traefik became dynamic by watching new events of orchestrator (docker, kubernetes, etc)

## Use Cases

- Reverse Proxy: sits in front of web servers and routes incoming requests to the appropriate backend service

  - redirects traffic between different services
  - handle SSL/TLS termination (process where reverse-proxy or load-balancer handles the encryption and decryption of HTTPS traffic,
    relieving backend servers from this computational overhead)
  - provide an additional layer of security by hiding backend server details

- API Gateway: acts as entrypoint for API requests

  - request/response transformation
  - e.g. query parameter manipulation: `/api/users?filter=active` (original URL) to `/api/users?status=active&version=v2` (transformed URL)

- authentication and authorization

- rate limiting

- Load Balancing: distribute incoming network traffic across multiple servers

  - prevent any single server from becoming a bottleneck
  - load balancing strategies: Round Robin, Weighted Round Robin, Least Connections, IP Hash

- Certificate Management: automatic SSL/TLS certificate management using Let's Encrypt
