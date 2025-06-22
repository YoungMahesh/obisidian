You are given a binary tree having 'N' nodes. Each node of the tree has an integer value.

Your task is to find the maximum average of node values of any subtree of the given tree

### method1: return maxAverage from every recursive function

```python
# BinaryTreeNode class for reference.
class BinaryTreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

# O(n) time, O(n) space, n-space for  recursive call stack
def maxSubtreeAverage(root):
    if root == None:
        return 0
    maxAvg, currSum, noOfEle = getMaxAvg(root)
    return maxAvg

def getMaxAvg(node):

    if node.left == None and node.right == None:
        return node.data, node.data, 1

    if node.right == None:
        leftMaxAvg, leftSum, leftCount = getMaxAvg(node.left)
        currSum = leftSum + node.data
        currCount = leftCount + 1
        currAvg = currSum / currCount
        if leftMaxAvg > currAvg:
            return leftMaxAvg, currSum, currCount
        else:
            return currAvg, currSum, currCount
    if node.left == None:
        rightMaxAvg, rightSum, rightCount = getMaxAvg(node.right)
        currSum = rightSum + node.data
        currCount = rightCount + 1
        currAvg = currSum / currCount
        if rightMaxAvg > currAvg:
            return rightMaxAvg, currSum, currCount
        else:
            return currAvg, currSum, currCount

    leftMaxAvg, leftSum, leftCount = getMaxAvg(node.left)
    rightMaxAvg, rightSum, rightCount = getMaxAvg(node.right)
    currSum = leftSum + rightSum + node.data
    currCount = leftCount + rightCount + 1
    currAvg = currSum / currCount
    if leftMaxAvg > rightMaxAvg:
        if leftMaxAvg > currAvg:
            return leftMaxAvg, currSum, currCount
    else:
        if rightMaxAvg > currAvg:
            return rightMaxAvg, currSum, currCount
    return currAvg, currSum, currCount
```

### method2: pass maxAverage value to the parameter every recursive function

```python
# BinaryTreeNode class for reference.
class BinaryTreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

# O(n) time, O(n) space
def maxSubtreeAverage(root):
    # we are using array instead of variable, as array[index] points to
        # same location in memory during recursion
    maxAverage = [float('-inf')]

    postOrderTraversal(root, maxAverage)

    return maxAverage[0]

def postOrderTraversal(node, maxAverage):
    if node == None:
        return [0, 0]

    [leftSum, leftNodes] = postOrderTraversal(node.left, maxAverage)
    [rightSum, rightNodes] = postOrderTraversal(node.right, maxAverage)

    # we will compare sum of each subtree with maxAverage on every level
    currSum = leftSum + rightSum + node.data
    currNodes = leftNodes + rightNodes + 1
    currAverage = currSum / currNodes
    maxAverage[0] = max(maxAverage[0], currAverage)

    return [currSum, currNodes]
```
