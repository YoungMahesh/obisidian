### classification

- single source shortest path algorithms
  - A\* algorithm:
    - informed search algorithm, with time-complexity: O(E + V log(V))
    - can handle negative edge weights
    - uses heuristics to guide its search which makes it much faster than Dijkstra's or Bellman-Ford for most graphs.
    - shortest path using heuristic approach
    - use: shortest path between two cities on a road network or two computers in a network
  - Dijkstra's algorithm:
    - greedy algorithm (heaps), with time-complexity: O(E log(V))
    - cannot handle negative weights
    - faster and simpler to implement compared to bellman-ford algorithm
    - use: shortest path between two cities on a road network or two computers in a network
  - Bellman Ford algorithm:
    - dynamic programming algorithm, with time time-complexity: O(VE)
    - can handle graphs with negative edge weights, including negative cycles
    - use: detect arbitrage in currency exchanges 
- MST (Minimum spanning tree) finding
  - Prism's algorithm:
    - vertex-based algorithm
    - weight of edge connecting to the mst (heap, hash-table)
    - cannot handle negative weights
    - time-complexity: E log(E), E == number of edges
    - used in applications where the graph is dense, such as image processing and natural language processing.
  - Kruskal's algorithm:
    - edge-based algorithm
    - ascending order of weight (sorting, hash-table)
    - can handle negative weights
    - time-complexity: V, V == number of vertices
    - used in applications where the graph is sparse, such as network design and routing.

### a\* path finder

The [A\* pathfinding algorithm](a__path-finder.excalidraw.excalidraw.png) is a graph traversal and path search algorithm that uses heuristics to estimate the most efficient path. It is a widely used algorithm in robotics, video games, and other applications where efficient navigation is required.

The A\* algorithm works by maintaining two sets of nodes:

- **Open set:** This set contains all of the nodes that have been discovered but not yet expanded.
- **Closed set:** This set contains all of the nodes that have been expanded.

The algorithm starts by adding the start node to the open set. Then, it iteratively expands the node with the lowest f score from the open set. The f score is calculated as follows:

```
f(n) = g(n) + h(n)
```

- `g(n)` is the cost of the path from the start node to the current node `n`.
- `h(n)` is the estimated cost of the path from the current node `n` to the goal node.

The heuristic function `h(n)` is what makes the A\* algorithm different from other path-finding algorithms. The heuristic function estimates the distance between the current node and the goal node. It is important to choose a good heuristic function, as this will affect the performance of the algorithm.

Once a node is expanded, its neighbors are added to the open set, if they are not already in the open or closed set. The cost of the path to each neighbor is calculated, and the f score is updated accordingly.

The algorithm terminates when the goal node is expanded. The path to the goal node can then be traced back by following the parent pointers of the nodes in the closed set.

```python
# implementation from bard
class Node:
  def __init__(self, position, parent=None, cost=0):
    self.position = position
    self.parent = parent
    self.cost = cost
    self.f = cost

  def __repr__(self):
    return f"Node({self.position}, {self.cost})"

def heuristic(node, goal):
  """Estimates the cost of the path from the current node to the goal node."""
  return manhattan_distance(node.position, goal.position)

def manhattan_distance(a, b):
  """Calculates the Manhattan distance between two points."""
  return abs(a[0] - b[0]) + abs(a[1] - b[1])

def AStar(start, goal):
  """Finds the shortest path between two nodes in a graph using the A* algorithm."""

  open_set = {start}
  closed_set = set()

  while open_set:
    current_node = min(open_set, key=lambda n: n.f)

    if current_node is goal:
      return reconstruct_path(current_node)

    open_set.remove(current_node)
    closed_set.add(current_node)

    for neighbor in current_node.neighbors:
      if neighbor in closed_set:
        continue

      new_cost = current_node.cost + cost(current_node, neighbor)
      if neighbor not in open_set or new_cost < neighbor.cost:
        neighbor.cost = new_cost
        neighbor.f = new_cost + heuristic(neighbor, goal)
        neighbor.parent = current_node
        open_set.add(neighbor)

  return None

def reconstruct_path(current_node):
  """Reconstructs the path to the goal node from the given node."""

  path = []
  while current_node is not None:
    path.append(current_node)
    current_node = current_node.parent

  path.reverse()
  return path

# Example usage:

start = Node((0, 0))
goal = Node((5, 5))

path = AStar(start, goal)

if path is not None:
  print("The shortest path is:")
  for node in path:
    print(node.position)
else:
  print("No path found.")
```

```python
import heapq

# O(w*h * log(w*h)) time, O(w*h) space
# where w == width of graph, h == height of graph
# we need *log(w*h) time due to heap
def aStarAlgorithm(startRow, startCol, endRow, endCol, graph):
    matrixValuesToNodes(graph)

    heap = [graph[startRow][startCol]]
    heap[0].fromStart = 0  # startNode's fromStart distance will be base for
    # for future fromStart distance calculations
    while len(heap) > 0:
        currNode = heapq.heappop(heap)
        if currNode.visited:
            continue
        currNode.visited = True

        if currNode.rowIdx == endRow and currNode.colIdx == endCol:
            break

        neighbors = getNeighbors(graph, currNode, endRow, endCol)
        for neighbor in neighbors:
            heapq.heappush(heap, neighbor)

    shortestPath = extractShortestPath(graph, endRow, endCol, startRow, startCol)
    return shortestPath

def extractShortestPath(graph, endRow, endCol, startRow, startCol):
    currNode = graph[endRow][endCol]
    if currNode.prevNode == None:
        # if endNode does not have any prevNode, then we failed to reach to the endNode
        return []

    shortestPath = []
    while currNode != None:
        shortestPath.append([currNode.rowIdx, currNode.colIdx])
        currNode = currNode.prevNode

    # we tracked path from endNode to startNode, hence we need to reverse the path
        # to problem asks path from startNode to endNode
    shortestPath.reverse()
    return shortestPath

def getNeighbors(graph, currNode, endRow, endCol):
    neighbors = []
    directions = [(-1,0), (0,1), (1,0), (0,-1)]
    for direction in directions:
        plusRow, plusCol = direction
        nextRow = currNode.rowIdx + plusRow
        nextCol = currNode.colIdx + plusCol
        if nextRow >= 0 and nextRow < len(graph) and nextCol >= 0 and nextCol < len(graph[0]):
            nextNode = graph[nextRow][nextCol]
            if nextNode.value != 0 or nextNode.visited:
                # only value == 0 is empty space from which path can be created
                continue
            calculateApproxDistance(graph, currNode, nextNode, endRow, endCol)
            neighbors.append(nextNode)
    return neighbors

def calculateApproxDistance(graph, currPrevNode, currNode, endRow, endCol):
    # this node is visited multiple times as neighbor of various nodes
    # heuristicDistance will remain same in visit
    if currNode.heuristicDistance == float('inf'):
        currNode.heuristicDistance = abs(endRow - currNode.rowIdx) + abs(endCol - currNode.colIdx)
    # fromStart is calculated multiple times considering who is prevNode
        # if we will optimize fromStart distance whenever possible
    if currNode.fromStart > 1+currPrevNode.fromStart:
        currNode.prevNode = currPrevNode
        currNode.fromStart = 1 + currPrevNode.fromStart
    currNode.total = currNode.heuristicDistance + currNode.fromStart

class Node:
    def __init__(self, value, rowIdx, colIdx):
        self.value = value
        self.rowIdx = rowIdx
        self.colIdx = colIdx
        self.total = float('inf')
        self.fromStart = float('inf')
        self.heuristicDistance = float('inf')
        self.prevNode = None
        self.visited = False

    # min-heap formed of these nodes, will check __lt__ function while sorting
    # here we are telling min-heap that element is considered small if it's self.total
        # is less than other
    def __lt__(self, nextNode):
        return self.total < nextNode.total

def matrixValuesToNodes(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            matrix[i][j] = Node(matrix[i][j], i, j)

```

### dijkstra's algorithm

[Dijkstra's algorithm](./dijkstra''s_algorithm.excalidraw.png) is a graph algorithm that finds the shortest paths from a single source node to all other nodes in a graph. It is an iterative algorithm that works by building a set of nodes that have been visited and a set of nodes that have not yet been visited. The algorithm starts by initializing the visited set to be empty and the distance to each node in the graph to be infinity, except for the source node, whose distance is set to 0.

At each iteration, the algorithm selects the node in the unvisited set with the shortest distance to the source node. It then marks that node as visited and updates the distances to all of its neighbors. If the distance to a neighbor through the selected node is shorter than the current distance to that neighbor, the distance is updated.

The algorithm terminates when all of the nodes in the graph have been visited. At that point, the distance to each node in the graph is the shortest distance from the source node to that node.

```python
import heapq
# O((v+e) * log(v)) time, O(v) space, where e == number of edges
# time is O(v+e)  as we are moving through multiple edges while visiting each vertex 
# & * log(v) as we are using heaps
def dijkstrasAlgorithm(start, edges):

    heap = [[0,start]]

    shortestPaths = [float('inf') for edge in edges]
    shortestPaths[start] = 0
    visited = set()

    while len(heap) > 0:
        [currDistance, currVertex] = heapq.heappop(heap)
        if currVertex in visited:
            continue
        visited.add(currVertex)

        for neighbor in edges[currVertex]:
            [neighborVertex, neighborDistance] = neighbor
            shortestDistToNeighbor = min(shortestPaths[neighborVertex], currDistance+neighborDistance)
            shortestPaths[neighborVertex] = shortestDistToNeighbor
            heapq.heappush(heap, [shortestDistToNeighbor, neighborVertex])

    for pathIdx in range(len(shortestPaths)):
        if shortestPaths[pathIdx] == float('inf'):
            shortestPaths[pathIdx] = -1

    return shortestPaths
```

### kruskal's algorithm

Kruskal's algorithm is a greedy algorithm that finds a minimum spanning tree (MST) of an undirected edge-weighted graph.
A MST is a subset of the edges of a graph that connects all of the vertices in the graph with the minimum total weight.
Kruskal's algorithm works by repeatedly adding the edge with the lowest weight to the MST,
as long as adding that edge does not create a cycle.

The steps of Kruskal's algorithm are as follows:

1. Sort all of the edges in the graph by weight, in increasing order.
2. Initialize the MST to be the empty set.
3. While there are still edges in the sorted list:
   Remove the edge with the lowest weight from the sorted list.
   If adding the edge to the MST does not create a cycle, add the edge to the MST.
   We detect cycle by using union-find algorithm
4. The MST is now the set of edges that have been added to the MST.

```python
def kruskalsAlgorithm(edges):
    modEdges = []
    for sourceIdx, vertex in enumerate(edges):
        # in given input, edge is given at both indices - sourceIdx and destinationIdx
        # hence we will only consider one out of two
        # let's create edge when destinationIdx > sourceIdx
        for edge in vertex:
            if sourceIdx < edge[0]:
                # edge modEdge contains - source at index0, destination at index1, weight at index2
                modEdges.append([sourceIdx, edge[0], edge[1]])

    # sort edges by considering weight
    sortedEdges = sorted(modEdges, key= lambda edge: edge[2])

    # now we will use union-find algorithm to pick minimum spanning tree
    parents = [ele for ele in range(len(edges))]
    ranks = [0 for ele in range(len(edges))]

    mst = [[] for _ in range(len(edges))]
    for edge in sortedEdges:
        [source, dest, weight] = edge
        sourceRoot = find(source, parents)
        destRoot = find(dest, parents)
        if sourceRoot != destRoot:
            # source and dest are not part of same set, means they are not connected in our mst
            # let's connect them and add them to our mst
            mst[source].append([dest, weight])
            mst[dest].append([source, weight])
            union(sourceRoot, destRoot, parents, ranks)

    return mst

def find(vertex, parents):
    if vertex != parents[vertex]:
        parents[vertex] = find(parents[vertex], parents)

    return parents[vertex]

def union(vertex1Root, vertex2Root, parents, ranks):
    if ranks[vertex1Root] < ranks[vertex2Root]:
        parents[vertex1Root] = vertex2Root
    elif ranks[vertex1Root] > ranks[vertex2Root]:
        parents[vertex2Root] = vertex1Root
    else:
        parents[vertex2Root] = vertex1Root
        ranks[vertex1Root] += 1
```

### Prism's algorithm

```python
import heapq

# O(e * log(v)) time, O(v+e) space - where e == number of edges, v == number of vertices
def primsAlgorithm(edges):
    # heap = [[distance, discoveredVerted, currVertex]]  
    heap = [[edge[1], edge[0], 0] for edge in edges[0]]  # considering vertex_at_index_0 as start_vertex
    # added all edges connected to vertex_0 to the heap
    heapq.heapify(heap)

    mst = [[] for _ in range(len(edges))]
    while len(heap) > 0:
        [distance, discoveredVertex, vertex] = heapq.heappop(heap)

        if len(mst[discoveredVertex]) == 0:
            mst[vertex].append([discoveredVertex, distance])
            mst[discoveredVertex].append([vertex, distance])

            for neighbor, neighborDistance in edges[discoveredVertex]:
                if len(mst[neighbor]) == 0:
                    heapq.heappush(heap, [neighborDistance, neighbor, discoveredVertex])

    return mst
```
