- do simple, essential tasks first
  - create profile-service, chat-service before recommendation-service

### profile service (store profiles)

- age, gender, location for match-recommendation
- 5 images/user as file on DFS (distributed file system) instead blob (binary large object in databases)
- username, token(insted of password)
- image service: database (profileId: imageUrl),(DFS) Distributed File system for storing actual images
  - it may be good idea, to create separate image service for images, it will help if we wish to use images for some tasks as machine-learning
- recommend matches

  - no of active users
  - database: as we are going to consider multiple inputs like gender, age, location, etc sql databases are preferable
    - we can use sharding(horizontal partitioning) on sql databases
    - partitioning data: users from location-beed will be stored in db @node-1, users from pune will be stored in db @node-2, etc
    - we can use master-replica database architecture

### matches service (track who matched to whom)

- note down people who got matched, derive probability by previous matches
- track to which types of profiles user is sending request, type of profiles it is already connecting
- using data from matcher server, provide future recommendations
- direct messaging
- create gateway service for authentication

  - after authentication gateway service will connect user information to various services such as profile-service

### chat service


- databases over text-files
  - mutability, ACID transaction guarantee, indexes to improve search
- file_sytem over database
  - faster_transfer, cheaper_processing for large-objects
- CDN
  - provides fast delivery large files
