### minimum subarray to sort
You have given an array 'arr' of integers. Find the minimum length of a subarray such that choosing/sorting this subarray will make the whole array sorted in ascending order

```python
# O(n log(n)) time, O(n) space
def findLength(arr, n):
    sortedArr = sorted(arr)

    leftIdx=0; rightIdx=len(arr)-1
    while leftIdx <= rightIdx and arr[leftIdx] == sortedArr[leftIdx]:
        leftIdx += 1
    while leftIdx <= rightIdx and arr[rightIdx] == sortedArr[rightIdx]:
        rightIdx -= 1

    return rightIdx-leftIdx+1
```