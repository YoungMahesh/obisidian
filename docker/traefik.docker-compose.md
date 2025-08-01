```yml
# https://doc.traefik.io/traefik/user-guides/docker-compose/basic-example/

services:
  traefik:
    container_name: "traefik"
    image: traefik:v3.3.3

    # traefik static configuration
    command:
      # enables the Traefik API on http to view traefik dashboard on http or https
      - --api.insecure=true

      # -------------- provider --------------------
      # https://doc.traefik.io/traefik/routing/providers/docker/#configuration-examples
      - --providers.docker=true
      
      # -------------- entrypoints ---------------------
      # https://doc.traefik.io/traefik/routing/entrypoints/#configuration-examples
      - --entrypoints.web.address=:80
      # here websecure is a custom name given to this specific entrypoint
      - --entryPoints.websecure.address=:443
      # redirect http to https
      # https://doc.traefik.io/traefik/routing/entrypoints/#http-options
      # https://doc.traefik.io/traefik/routing/entrypoints/#redirection
      - --entryPoints.web.http.redirections.entryPoint.to=websecure

      # ------------ certification / domain-provider ------------------
      # https://doc.traefik.io/traefik/https/acme/#configuration-examples
      # https://doc.traefik.io/traefik/routing/entrypoints/#tls
      # https://doc.traefik.io/traefik/user-guides/docker-compose/acme-tls/#docker-compose-with-lets-encrypt-tls-challenge
      # you will receive emails when certification is near expiration or if there are any problems with certificates
      # here myresolver is a custom name given to certification provider
      # acme is name of communication protocol that automates the process of issuing and managing certificates
      - --certificatesresolvers.myresolver.acme.email=xyz@example.com
      # set ./letsencrypt/acme.json file permission to `chmod 600 acme.json` if got file access error
      - --certificatesresolvers.myresolver.acme.storage=/letsencrypt/acme.json
      - --certificatesresolvers.myresolver.acme.httpChallenge.entryPoint=web

      # ------------------ log file ---------------------------
      # https://doc.traefik.io/traefik/observability/logs/
      # DEBUG = detailed debugging, INFO = standard opearation, ERROR = only critical errors
      #- "--log.level=DEBUG"
      # `docker logs traefik` to view logs, or you can define file which will store logs

    # --------------- dynamic configuration -------------------
    labels: 
      - "traefik.http.routers.trfk.tls.certresolver=cert0"
      - "traefik.http.routers.trfk.rule=Host(`trfk.xyz.com`)"
      - "traefik.http.services.trfk.loadbalancer.server.port=8080"

    ports:
      # http requests are received on 80
      - "80:80"

      # https requests are received on 443
      - "443:443"

      # The Web UI port http://0.0.0.0:8080 (enabled by --api.insecure=true)
      - "8080:8080"

    volumes:
      # Let Traefik listen to the Docker events, so it can respond to dynamic configuration defined on container labels
      # https://doc.traefik.io/traefik/reference/install-configuration/providers/docker/#endpoint
      - /var/run/docker.sock:/var/run/docker.sock

      # mount ./letsencrypt to container, so we can store certificates in current directory 
      - ./letsencrypt:/letsencrypt



  # a service to test proper working of traefik
  whoami:
    container_name: "whoami"
    # A container that exposes an API to show its IP address
    image: "traefik/whoami"
    # initiate services with specific profile using `docker compose --profile production up -d`
    profiles: [production]
    # traefik dynamic configuration
    labels:
      # ----------------------- router ----------------------
      # https://doc.traefik.io/traefik/routing/providers/docker/#routers

      # set domain name
      # connect to certification provider from static configuration
      - "traefik.http.routers.whoami.tls.certresolver=myresolver"
      - "traefik.http.routers.whoami.rule=Host(`whoami.com`) || Host(`whoami2.com`) || Host(`www.whoami.com`)"

      # 2. local path (alternative to certification)
      # to view response from container, you can execute: curl http://whoami.localhost
      # traefik: docker service, http: protocol, routers: traefik configuration, frontend: router name 
      # (user defined name for config), rule: option for configuration (here rule for router)
      # - "traefik.http.routers.whoami.rule=Host(`whoami.localhost`)"

      # ----------------- service -------------------------
      # provide service-name for this container
      # trafik-service and docker-service are two different concepts, they does not have same name by default
      # https://doc.traefik.io/traefik/routing/providers/docker/#services
      # here 'whoami' is a custom service-name for this container
      - "traefik.http.services.whoami.loadbalancer.server.port=80"


	  # ---------------- basic #auth -------------------
	  # https://doc.traefik.io/traefik/middlewares/http/basicauth/
	  # -n = no file (output to console); 
	  # -b = batch mode (pick password from cli instead of prompt)
	  # -B = use bcrypt algorithm to hash password
	  # htpasswd -nbB <username> <password>
	  # Note: when used in docker-compose.yml all dollar signs in the hash need to be doubled for escaping.
	  # sed -e == sed expression; here sed edits content to double $ signs
	  # echo $(htpasswd -nbB user1 password1) | sed -e s/\\$/\\$\\$/g
	  - "traefik.http.middlewares.whoami.basicauth.users=person1:$$apr1$$H6uskkkW$$IgXLP6ewTrSuBkTrqE8wj/"
	  # set multiple users
	  - "traefik.http.middlewares.whoami.basicauth.users=test:$$apr1$$H6uskkkW$$IgXLP6ewTrSuBkTrqE8wj/,test2:$$apr1$$d9hr9HBB$$4HxwgUir3HP4EsggP/QNo0"
	  # apply middleware to router (necessory)
	  - "traefik.http.routers.whoami.middlewares=whoami@docker"

 
    networks:
      - traefik_default

networks:
  # verify traefik network name using `docker network ls`
  traefik_default:
    external: true
```
