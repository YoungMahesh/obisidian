- heap is a complete binary tree
- in min-heap, every node's value is less than or equal to it's children-node's values
- heap can be stored in the form of array
  - index of firstChild of heap-node = `2 * current_index + 1`
  - index of secondChild of heap-node = `2 * current_index + 2`
  - index of parent of heap-node = `floor( (current_index-1) / 2)`
- insert a new element
  - append element to the to the heap-array
  - now, as last element may not be at the correct position, we move it upward in heap-tree, method of moving up element in heap is called as `siftUp`
- remove top element
  - swap element at root-node which is at index-0 in heap-array with last-element
  - remove last element
  - now, the element at index-0 may not be at the correct position, hence we move it downward in heap-tree, mothod of moving down element is called as `siftDown`
- build heap
  - we can build heap we siftDown elements starting form middle of the array to the start of the array

```python
class MinHeap:
    def __init__(self, array):
        self.heap = self.buildHeap(array)

    # O(n log(n)) time, O(1) space
    def buildHeap(self, array):
        # heap is a complete binary tree, hence all nodes after half of the heap-array are leaf nodes
            # hence, we can build heap if we siftDown elements from middle of the array to the start of the array
        middleIndex = len(array) // 2
        for currIdx in range(middleIndex, -1, -1):
            self.siftDown(array, currIdx)
        return array

    # O(log(n)) time, O(1) space
    def siftDown(self, heap, currentIdx):
        # we use this function while building heap, hence may not have self.heap,
            # during execution of siftDown, hence we are accessing heap-array
            # from function-input parameters
        firstChildIdx = 2 * currentIdx + 1
        while firstChildIdx < len(heap):
            idxToSwap = firstChildIdx
            secondChildIdx = firstChildIdx + 1
            if secondChildIdx < len(heap) and heap[secondChildIdx] < heap[firstChildIdx]:
                idxToSwap = secondChildIdx

            if heap[idxToSwap] < heap[currentIdx]:
                heap[idxToSwap], heap[currentIdx] = heap[currentIdx], heap[idxToSwap]
                currentIdx = idxToSwap
                firstChildIdx = 2 * currentIdx + 1
            else:
                break

    # O(log(n)) time, O(1) space
    def siftUp(self, currentIdx):
        heap = self.heap
        parentIdx = (currentIdx-1) // 2
        while parentIdx >= 0 and heap[parentIdx] > heap[currentIdx]:
            heap[parentIdx], heap[currentIdx] = heap[currentIdx], heap[parentIdx]
            currentIdx = parentIdx
            parentIdx = (currentIdx-1) // 2

    # O(1) time, O(1) space
    def peek(self):
        return self.heap[0]

    # O(log(n)) time, O(1) space
    def remove(self):
        toRemove = self.heap[0]
        heap = self.heap
        heap[0], heap[-1] = heap[-1], heap[0]
        heap.pop()
        self.siftDown(heap, 0)
        return toRemove

    # O(log(n)) time, O(1) space
    def insert(self, value):
        heap = self.heap
        heap.append(value)
        self.siftUp(len(heap)-1)
```
