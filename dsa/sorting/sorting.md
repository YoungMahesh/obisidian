### radix sort

[radix-sort-diagram](radix-sort.excalidraw.md)
Radix sort is a non-comparative sorting algorithm that works by sorting elements digit by digit. This is done by creating buckets for each digit value, and then distributing the elements into the appropriate buckets. This process is then repeated for each digit, starting with the least significant digit and moving to the most significant digit.

```python
# walk through before writing code example for such large algorithms, to explain and confirm steps
# O(n*size_max_n) time, where size_max_n == length of largest/max number, n == length of array
# O(n) space
def radixSort(array):
    if len(array) == 0:
        return []

    maxNum = max(array)
    maxNumLength = len(str(maxNum))
    for digitIdx in range(maxNumLength):
        countingSort(array, digitIdx)
    return array

def countingSort(array, digitIdx):

    # step1: count numbers according to digitIdx
    countsArr = [0] * 10
    for num in array:
        currDigit = (num // 10**digitIdx) % 10
        countsArr[currDigit] += 1

    # step2: determine startIndices from end for current sortedArray using countsArr
    sortIndices = [0] * 10
    sortIndices[0] = countsArr[0]
    for idx in range(1, 10):
        sortIndices[idx] = countsArr[idx] + sortIndices[idx-1]

    # step3: place numbers in the sortedArray by referring to sortIndices
    # we will start from last number to first number to retain sorted-positions from
        # previous iterations
    sortedArray = [0] * len(array)
    for i in range(len(array)-1, -1, -1):
        num = array[i]
        currDigit = (num // 10**digitIdx) % 10
        # counting start from 1, indexing starts from 0, hence we reduce index position by 1
        sortIndices[currDigit] -= 1
        sortedIdx = sortIndices[currDigit]
        sortedArray[sortedIdx] = num


    # step4: register new sorted positions in array
    for i in range(len(array)):
        array[i] = sortedArray[i]
```

### heap sort

Heap sort is a comparison-based sorting algorithm that works by building a heap data structure from the input array.

A max-heap is a special type of binary tree in which the parent node is always greater than or equal to its child nodes. This property is maintained by repeatedly swapping the parent node with the largest child node until the heap is in order.

Once the heap is built, heap sort works by repeatedly removing the largest element from the heap and inserting it into the sorted part of the array. This is done by swapping the root node of the heap with the last element of the array and then rebuilding the heap. The process continues until the heap is empty and the array is sorted.

```python
# O(n log(n)) time, O(1)
def heapSort(array):
    convertToMaxHeap(array)
    # move from last-index to second-index, with each iteration putting one element
        # in it's sorted position
    for endIdx in range(len(array)-1, 0, -1):
        # first index is largest element from 0th index to end-index
        array[0], array[endIdx] = array[endIdx], array[0]

        # restructure max-heap, so largest element from 0 to endIdx-1 will be sifted to index-0
        siftDown(array, 0, endIdx-1)

    return array


def convertToMaxHeap(array):
    # first parent of the heap binary-tree is normally at the centre of the array
    firstParentIdx = len(array) // 2

    # we are iterating from middle to left, and not left middle
        # as 0th index will be largest element, but we cannot place it to 0th position
        # if that element is at end of the array and we are moving from left to middle
    for parentIdx in range(firstParentIdx, -1, -1):
        siftDown(array, parentIdx, len(array)-1)

def siftDown(array, parentIdx, endIdx):
    # max-heap is binary tree stored in form of list/array
    childOneIdx = parentIdx * 2 + 1

    # swap elements of tree until children-value > parent-value
    while childOneIdx <= endIdx:
        # swap child with bigger-value than (parent and another child) with parent
        idxToSwap = childOneIdx
        childTwoIdx = childOneIdx + 1
        if childTwoIdx <= endIdx and array[childTwoIdx] > array[childOneIdx]:
            idxToSwap = childTwoIdx

        if array[idxToSwap] < array[parentIdx]:
            break

        # if any ne child-value > parent-value swap child and parent
        array[idxToSwap], array[parentIdx] = array[parentIdx], array[idxToSwap]
        parentIdx = idxToSwap
        childOneIdx = parentIdx * 2 + 1
```

### merge sort

Merge sort is a divide-and-conquer sorting algorithm. It works by recursively dividing the array into two halves, sorting each half, and then merging the two sorted halves back together. This process is repeated until the entire array is sorted.

```python
# time: O(n log(n)), space: O(n)

def merge(array, helperArray, leftStart, leftEnd, rightStart, rightEnd):
    # i to iterate over leftPart, j to iterate over rightPart, k to iterate over helperArray
    i = leftStart; j = rightStart; k = leftStart

    # sort helperArray section from leftStart to rightEnd by comparing values at array
    while i <= leftEnd or j <= rightEnd:
        if i > leftEnd:
            helperArray[k] = array[j]
            j += 1
        elif j > rightEnd:
            helperArray[k] = array[i]
            i += 1
        elif array[i] <= array[j]:
            helperArray[k] = array[i]
            i += 1
        elif array[i] > array[j]:
            helperArray[k] = array[j]
            j += 1
        k += 1

    # copy sorted part of helperArray to array
    for m in range(leftStart, rightEnd+1):
        array[m] = helperArray[m]


def divideAndMerge(array, helperArray, rangeStart, rangeEnd):
    if rangeStart >= rangeEnd:
        return

    midIdx = int((rangeStart+rangeEnd) / 2)
    divideAndMerge(array, helperArray, rangeStart, midIdx)
    divideAndMerge(array, helperArray, midIdx+1, rangeEnd)
    merge(array, helperArray, rangeStart, midIdx, midIdx+1, rangeEnd)

def mergeSort(array):
    helperArray = [0 for ele in array]
    divideAndMerge(array, helperArray, 0, len(array)-1)
    return array
```

```
# we can never merge two sorted arrays in-place by swapping, we need extra-space

arr = [2, 3, 8, 9, 5, 5, 6]
        0 1  2  3  4  5  6
mid = (0+6)/2 => 6/2 => 3
section1 = 0 -> 3
section2 = 4 -> 6

if we try to merge two sorted sections of array 1, just by swapping with this formula:
i, j = 0, 4
while i < j:
	if arr[i] <= arr[j]:
		i+=1
	elif arr[j] > arr[i]:
		arr[i], arr[j] = arr[j], arr[i]
		i += 1

when i reaches at index-2 with value-9, it will get swapped index-4 with value-5
but now, index-5 have value smaller than 9, so the end result will not be sorted
```

### quick sort

Quicksort is a divide-and-conquer algorithm for sorting an array. It works by selecting a pivot element from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot. The sub-arrays are then sorted recursively.

```python
# considering index-0 as pivot at every step
# time: O(n^2) in worst case, O(n log(n)) in average case
# space: O(n) in worst case, O(log (n)) in average
# space can be O(log (n)) for sure, if we choose to iterate smaller part of the partition to iterate first, space is consumed by recursive call-stack

def quickSortHelper(array, rangeStart, rangeEnd):
    if rangeStart >= rangeEnd:
        return

    pivotIdx = rangeStart
    startIdx = rangeStart+1
    endIdx = rangeEnd

    # we are considering left-partition should have elements with value either less
        # or equal to the pivot-value
    # and right-partition should have elements with value greater than pivot-value
    while startIdx <= endIdx:
        if array[startIdx] > array[pivotIdx] and array[endIdx] <= array[pivotIdx]:
            array[startIdx], array[endIdx] = array[endIdx], array[startIdx]
            startIdx += 1
            endIdx -= 1
        elif array[startIdx] <= array[pivotIdx]:
            startIdx += 1
        elif array[endIdx] > array[pivotIdx]:
            endIdx -= 1

    # now startIdx > endIdx, endIdx represents boundary where all elements which
            # are either less than or equal to pivot ends
    # also, startIdx may have gone out of range, if this array section is sorted,
            # but endIdx cannot go out of range as pivotIdx is at 0th position
            # and as soon as pivot-value == end-value, endIdx stops movement
    # so, now we will place pivot at it's correct postion
    array[endIdx], array[pivotIdx] = array[pivotIdx], array[endIdx]

    # sort array again except pivotIdx, as pivotIdx have sorted value
    quickSortHelper(array, rangeStart, endIdx-1)
    quickSortHelper(array, endIdx+1, rangeEnd)


def quickSort(array):
    quickSortHelper(array, 0, len(array)-1)
    return array
```

### bubble sort

Bubble sort is a simple sorting algorithm that works by repeatedly comparing adjacent elements and swapping them if they are in the wrong order. This process is repeated until the array is sorted.
we can do two improvements

1. count iteration: at every iteration last element is sorted, hence we will not consider that element in next iteration
2. track isSorted: if no swap of two elements happened in any iteration, then array is already sorted

```python
def bubbleSort(array):
    # exchange current element with next element if current-element < next-element, do this upto iteration == len(array)
    # at the end of every iteration we know that the last-element is in sorted position as we bubbled it until end

    for count in range(0, len(array)):
	    isSorted = True
	    # we are going until len(array)-1, as we are accesstion i+1 element also
        for i in range(0, len(array)-1-count):
            # we have already sorted count-numbers of last elements, hence we don't need to look into them in this iteration
            if array[i] > array[i+1]:
                array[i], array[i+1] = array[i+1], array[i]
                isSorted = False
        if isSorted:
	        break
        count += 1

    return array
```

### selection sort

works by repeatedly finding the smallest (or largest) element in an unsorted list and swapping it with the first element in the unsorted list. This process is repeated until the entire list is sorted.

```python
def insertionSort(array):
    for i in range(len(array)):
        selectedIdx = i
        for j in range(i+1, len(array)):
            if array[selectedIdx] > array[j]:
                selectedIdx = j
        array[i], array[selectedIdx] = array[selectedIdx], array[i]

    return array
```

### insertion sort

works by iterating over an unsorted array and inserting each element into its correct position in the sorted portion of the array.
The algorithm starts by treating the first element as the sorted portion of the array. It then iterates over the remaining elements in the array, comparing each element to the sorted portion of the array and inserting it into its correct position.

```python
def insertionSort(array):
    for i in range(1, len(array)):
        j = i
        while j > 0 and array[j] < array[j-1]:
            array[j], array[j-1] = array[j-1], array[j]
            j -= 1

    return array
```
