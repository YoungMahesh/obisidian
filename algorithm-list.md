## Dijkstra's algorithm
- graph search algorithm that finds the shortest path from a starting node to all other nodes in a graph
```python
import heapq
class Solution:
    def dijkstra(self, V, adj, S):

        visited = [False for _ in range(V)]
        heap = [(0, S)]

        wgtMap = {S: 0}
        maxWgt = 10 ** 9
        for i in range(V):
            if i != S:
                wgtMap[i] = maxWgt


        while len(heap):
            weight, node = heapq.heappop(heap)
            if visited[node]:
                continue
            visited[node] = True

            neighbors = adj[node] if node < len(adj) else []
            for ngNode, ngWgt in neighbors:
                wgtMap[ngNode] = min(wgtMap[ngNode], weight + ngWgt)
                heapq.heappush(heap, (wgtMap[ngNode], ngNode))

        shortest = []
        for i in range(V):
            shortest.append(wgtMap[i])

        return shortest
```
## Bellman-Ford
- graph search algorithm that finds the shortest path from a single source node to all other nodes in a weighted directed graph, even if the graph contains negative edge weights according to some resources. 
- It's particularly useful when Dijkstra's algorithm, which is faster, cannot be used due to negative edge weights.
- Why does this algorithm work?
	- Inductive Argument: After \(k\) passes, all shortest paths using at most \(k\) edges are correctly computed.
	- By \(n-1\) Passes: All shortest paths (which cannot have more than \(n-1\) edges) are found.
	- No Negative Cycles: If there are no negative cycles, the shortest path is well-defined and will be found.
```python
class Solution:
    def bellman_ford(self, V, edges, S):
        maxW = 10 ** 9
        shortest = [maxW for _ in range(V)]
        shortest[S] = 0

        for _ in range(V):
            # u = from, v = to, w = weight
            for u, v, w in edges:
                # get shortest weight, though relaxation of edges
                if shortest[u] != maxW and shortest[u] + w < shortest[v]:
                    shortest[v] = shortest[u] + w

        # if we get reduced reduced weight on one more relaxation, then graph contains negative weight cycle
        for u, v, w in edges:
            if shortest[u] != maxW and shortest[u] + w < shortest[v]:
                return [-1]

        return shortest

```