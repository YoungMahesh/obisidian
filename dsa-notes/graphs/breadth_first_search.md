### shortest alternate colored path

Consider a directed graph of 'N' nodes where each node is labeled from '0' to 'N-1'.

Each edge of the graph is either 'red' or 'blue' colored.

You are given two arrays, 'redEdges' and 'blueEdges', whose each element is in the form [i, j], denoting an edge from node 'i' to node 'j' of the respective color

Your task is to compute an array 'answer' of size 'N', where 'answer[i]' stores the length of the shortest path from node '0' to node 'i' such that the edges along the path have alternate colors. If there is no such path from node '0' to 'i', then 'answer[i] = -1'

```python
from queue import Queue

# we are going to use breadth first search to find shortest path
# we will also track color of edge through which we reached at the given node
	# so we can visit nodes using alternate color edges
# O(e) time, O(n+e) space, where, e == number of red+blue edges, n == number of nodes
def shortestAlternateColoredPath(n,  redEdges,  blueEdges):
	# create adjacency list
	redNeighbors = dict()
	for edge in redEdges:
		[start, end] = edge
		if start in redNeighbors:
			redNeighbors[start].append(end)
		else:
			redNeighbors[start] = [end]
	blueNeighbors = dict()
	for edge in blueEdges:
		[start, end] = edge
		if start in blueNeighbors:
			blueNeighbors[start].append(end)
		else:
			blueNeighbors[start] = [end]

	q = Queue()
	visited = set()
	shortestPaths = [float('inf')] * n
	shortestPaths[0] = 0

	# queue-format: [node, prevEdgeColor, distanceTraveled]
	q.put([0, None, 0])
	while q.qsize() > 0:
		[currNode, edgeColor, distance] = q.get()

		# skip already visited nodes
		if (currNode, edgeColor) in visited:
			continue
		visited.add((currNode, edgeColor))

		# we are visiting this node first time, hence current distance is shortest path
		shortestPaths[currNode] = min(shortestPaths[currNode], distance)

		# visit neighbors
		if edgeColor == None or edgeColor == 'RED':
			# as we reached current node through 'RED' edge, we will visit further nodes only through 'BLUE' edges
				# to fullfil requirement of alternate paths
			if not currNode in blueNeighbors:
				blueNeighbors[currNode] = []
			for nei in blueNeighbors[currNode]:
				q.put([nei, 'BLUE', distance+1])
		if edgeColor == None or edgeColor == 'BLUE':
			if not currNode in redNeighbors:
				redNeighbors[currNode] = []
			for nei in redNeighbors[currNode]:
				q.put([nei, 'RED', distance+1])

	for i in range(len(shortestPaths)):
		if shortestPaths[i] == float('inf'):
			shortestPaths[i] = -1

	return shortestPaths
```
