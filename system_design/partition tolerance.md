distributed system continues to operate even when network partitions (communication breakdown) occur between nodes in the system

## CAP theorem and network partition

CAP (Consistency, Availability and Partition tolerance) theorem states in the presence of a network partition distributed system must choose from:
- Availability: every request receives a (non-error) response
- Consistency: all nodes see the same data at the same time

## How systems handle partition tolerance
- AP (Availability + Partition tolerance) Systems: sacrifice availability during partition to maintain consistency (e.g. HBase)
	- [[consistency#eventual consistency]]
- CP (Consistency + Partition tolerance) Systems: sacrifice consistency during a partition to remain available (e.g. DynamoDB)
