refers to how up-to-date and synchronized the data is across different nodes


## strong consistency
## eventual consistency
- given enough time and in absence of new updates, all replicas in distributed system will converge to the same value
- in other words, after updates stop, all nodes will _eventually_ have same data, but immediate consistency is not guaranteed
- e.g. when you upload profile picture on social network. on one server your picture appears immediately, but on another server it might take few seconds to update.
	- after short period, all servers will show your new picture

### why use eventual consistency
- High availability: systems can respond to read and write requests even when some nodes are non-reachable or slow
- Scalability: scale horizontally across many servers and data centers
- partition tolerance: system can continue to operate even if network partitions occur

