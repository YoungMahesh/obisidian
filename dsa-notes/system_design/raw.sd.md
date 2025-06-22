### framework
- which features we will implement first
- which features have highest priority such that they cannot be shutdown during overload
- what data will go into database of specific service


### concepts
- master-replica/primary-secondary architecture
  - server named as "master" will execute write operation on all of it's "replica" servers"
  - data will be read from multiple "replica" server, which reduces load on master-server, and increases data availability
  - if master-server fails, one of the replica server will act as a master-server
  
### tinder

### whatsapp

- group messaging
  - we will use websockets for chatting
  - put limit on number of users in a group, as it will lead to server overload
- sent+delivered+read receipts (ticks which tell sender about status of their message)
  - database: {group_id: user_id}A
  - we need to decide what is priority, so when server gets too much loads in festivals or emergency, sending messages can be prioritized by disabling last-seen fetures
- online/last seen
  - a database should have timestamp of every user containing information, when he/she was online last time
  - one way to track last-seen, as store timestamp whenever user shows some activity, e.g. requests server for status of some person, sends message to some person, etc
- image sharing
- chat are temporary/permanent
- every server supports a limited number of users, hence we need load balancer which decide through which server user connect with others using websockets
