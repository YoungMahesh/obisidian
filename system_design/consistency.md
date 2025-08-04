#database/concepts

refers to how up-to-date and synchronized the data is across different nodes
## strong consistency
- after a write completes, any subsequent read will read will return that value or more recent one
- Guarantee: all clients will see the most recent value
- e.g. Traditional relational databases
- use case: banking and financial transactions
## eventual consistency
- given enough time and in absence of new updates, all replicas in distributed system will converge to the same value
- in other words, after updates stop, all nodes will _eventually_ have same data, but immediate consistency is not guaranteed
- e.g. Amazon DynamoDB, DNS
- use case: when you upload profile picture on social network. on one server your picture appears immediately, but on another server it might take few seconds to update.
	- after short period, all servers will show your new picture

### why use eventual consistency
- High availability: systems can respond to read and write requests even when some nodes are non-reachable or slow
- Scalability: scale horizontally across many servers and data centers
- partition tolerance: system can continue to operate even if network partitions occur


## sequential  consistency
- sequential from user point of view
- the result of execution is as if all operations are executed in some sequential order, and the operations of each individual process appear in this sequence in the order issued
- guarantee: operations from a single client are seen in order, but the global order may differ
- use case: collaborative document editing

## causal consistency
- writes that are causally related must be seen by all processes in the same order. concurrent writes may be seen in a different order on different nodes
- guarantee: if operation A might have influenced operation B, everyone sees A before B
- use case: social media feeds
	- if Alice posts a status and then Bob comments on it, everyone should see Alice's post before Bob's comment, even if updates reach different users at different times