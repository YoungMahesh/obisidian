#dsa
### Partition to K equal sum subsets

You are given an array of 'N' integers, and a positive integer 'K'.

You need to determine if it is possible to divide the array into 'K' non-empty subsets such that the sum of elements of each subset is equal

```python
# O(K * 2^n) time, O(n) space
# time is O(K*2^n) as we are going through recursion determine if we should include given element for our current subset or not
  # we are going to do this recursion, K times
# O(n) space is taken up by recursive-call stack O(n) + used_arr O(n)
def canPartitionKSubsets(arr, n, K):
    totalSum = sum(arr)
    subsetSum = totalSum / K
    used = [False] * len(arr)

    def backtrack(i, k, currSum):
        if k == 0:
            return True
        if currSum == subsetSum:
            return backtrack(0, k-1, 0)

        for j in range(i, len(arr)):
            if used[j] or currSum + arr[j] > subsetSum:
                continue
            used[j] = True
            if backtrack(j+1, k, currSum+arr[j]):
                return True
            used[j] = False

        return False

    return backtrack(0, K, 0)
```
