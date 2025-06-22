
### find nodes at distance k
You're given the root node of a Binary Tree, a `target` value of a node that's contained in the tree, and a positive integer `k`
Write a function that returns the values of all the nodes that are exactly distance `k` from the node with `target` value 
```python
from queue import Queue

# This is an input class. Do not edit.
class BinaryTree:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

# brute force approach
# store parents-nodes of all values in binary tree in a hash-table
        # this way we converted tree into a graph
# now we will do breadth first search from the target node until distance k
# O(n) time, O(n+h)->O(n) space, n == number of nodes, h == height of the tree
def findNodesDistanceK(tree, target, k):
    parents = dict()
    registerParents(tree, None, parents)
    targetNode = getTargetNode(tree, target)
    return getValuesAtDistanceK(targetNode, parents, k)

def getValuesAtDistanceK(tree, parents, k):
    visited = set()
    q = Queue()
    q.put(tree)
    q.put(None)

    while q.qsize() > 0:
        if k == 0:
            return getElements(q)
        currNode = q.get()
        if currNode == None:
            k -= 1
            q.put(None)
            continue
        # add parent and children
        temp = [parents[currNode.value], currNode.left, currNode.right]
        for ele in temp:
            if ele != None and ele.value not in visited:
                q.put(ele)
        visited.add(currNode.value)

    return []

def getElements(q):
    result = []

    # we know last value will be None, so we will not process it
    while q.qsize() > 1:
        currNode = q.get()
        result.append(currNode.value)
    return result

def getTargetNode(node, target):
    if node == None:
        return None
    if node.value == target:
        return node
    leftPart = getTargetNode(node.left, target)
    if leftPart != None:
        return leftPart
    return getTargetNode(node.right, target)

def registerParents(node, currParent, parents):
    if node == None:
        return
    parents[node.value] = currParent
    registerParents(node.left, node, parents)
    registerParents(node.right, node, parents)
```


### is tree symmetrical
A tree is symmetrical if left and right subtrees are mirror images of each other
```
Example of a symmetrial tree:
            1
         /      \
        2        2
       / \      / \
      3   4    4   3
     / \          / \
    5   6        6   5
```
```python
# This is an input class. Do not edit.
class BinaryTree:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

# we will iterate both sides at the same time by using stacks
# on left side, we will go first to the left and then to right
# on right side, we will go first to the right and then to the left
# O(n) time, O(n) space
def symmetricalTree(tree):
    if tree == None:
        return True
    if tree.left == None and tree.right == None:
        return True
    if tree.left == None or tree.right == None:
        return False
    
    leftSideStack = [tree.left]
    rightSideStack = [tree.right]

    while len(leftSideStack) > 0 and len(rightSideStack) > 0:
        leftNode = getNextNode(leftSideStack, True)
        rightNode = getNextNode(rightSideStack, False)
        if leftNode.value != rightNode.value:
            return False

    return len(leftSideStack) == 0 and len(rightSideStack) == 0

def getNextNode(nodesStack, isLeftSide):
    currNode = nodesStack.pop()

    if isLeftSide:
        # for left side we are appending right first, as during pop, 
        # currNode.right will be removed, after currNode.left
        if currNode.right != None:
            nodesStack.append(currNode.right)
        if currNode.left != None:
            nodesStack.append(currNode.left)
    else:
        if currNode.left != None:
            nodesStack.append(currNode.left)
        if currNode.right != None:
            nodesStack.append(currNode.right)

    return currNode
```


### traverse binary tree
```python
def traverseInReverse(tree, array):
	traverseInReverse(tree.right)
	array.append(tree.value)
	traverseInReverse(tree.left)

def traverseInOrder(tree, array):
	traverseInOrder(tree.left)
	array.append(tree.value)
	traverseInOrder(tree.right)
```

## Binary Search Tree (BST)

### repair BST
You're given a Binary Search Tree (BST) that has at least 2 nodes and that only has nodes with unique values. Exactly two nodes in the BST have had their values swapped, therefore breaking BST. Write a function that returns a repaired version of the tree with all values on the correct nodes
```python
# This is an input class. Do not edit.
class BST:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

# brute force approach:
# iterate through bst in inOrder and we will get sorted array
# now we will compare position of every number in this sorted array using two pointers
# we will replace two locations where we find mismatch
# if we find mismatch at only one position, then we will replace that position with 
        # next-node

# optimal approach
# do in-order traversal of tree, with three pointers
        # i) prevNode, ii) nodeOne, iii) nodeTwo
# we find mismatch and nodeOne == None, then we assign nodeOne=prevNode, nodeTwo = currNode
    # if nodeOne != None, then nodeTwo = prevNode
# replace values of nodeOne and nodeTwo
# O(n) time, O(h) space

class TreeInfo:
    def __init__(self):
        self.prevNode = None
        self.nodeOne = None
        self.nodeTwo = None

def repairBst(tree):
    treeInfo = TreeInfo()
    head = tree
    findMismatchedNodes(tree, treeInfo)
    treeInfo.nodeOne.value, treeInfo.nodeTwo.value = treeInfo.nodeTwo.value, treeInfo.nodeOne.value
    return head

# prevNode cannot be passed as parameter, as when we come from left node to center-node
    # prevNode == None instead leftNode if we are passing it as a parameter
def findMismatchedNodes(currNode, treeInfo):
    if currNode == None:
        return

    findMismatchedNodes(currNode.left,  treeInfo)

    # we are doing in-order traversal hence, current-node should always have greater
        # value than previous-node
    if treeInfo.prevNode != None and currNode.value < treeInfo.prevNode.value:
        if treeInfo.nodeOne == None:
            treeInfo.nodeOne = treeInfo.prevNode
            # if we does not find nodeTwo in future, currNode is going to be the 
            # node with which we will swap preNode
            treeInfo.nodeTwo = currNode
        else:
            treeInfo.nodeTwo = currNode

    # when the processing of currNode ends, we mark currNode as prevNode
    treeInfo.prevNode = currNode

    findMismatchedNodes(currNode.right,  treeInfo)

```



### create BST
given a non-empty array of integers representing a pre-order traversal of binary search tree (BST), write a function which creates BST and returns it's root node 
In pre-order traversal we visit: i) current node ii) left subtree iii) right subtree
```python
# This is an input class. Do not edit.
class BST:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

# O(n^2) time, O(n) space
def reconstructBst(preOrderTraversalValues):
    head = BST(preOrderTraversalValues[0])

    for i in range(1, len(preOrderTraversalValues)):
        addNodeToBST(head, preOrderTraversalValues[i])
    
    return head

def addNodeToBST(head, nodeVal):
    currNode = head
    
    while True:
        if nodeVal < currNode.value:
            if currNode.left == None:
                currNode.left = BST(nodeVal)
                break
            else:
                currNode = currNode.left
        else:
            if currNode.right == None:
                currNode.right = BST(nodeVal)
                break
            else:
                currNode = currNode.right
    
    return currNode

```