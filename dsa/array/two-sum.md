```python
# O(n^2) time, O(1) space
def twoSum(self, nums: List[int], target: int) -> List[int]:
    for i in range(len(nums)):
        for j in range(i+1, len(nums)):
            if nums[i] + nums[j] == target:
                return [i, j]
    return []
```

```python
# O(n) time, O(n) space
def twoSum(self, nums: List[int], target: int) -> List[int]:
    numsMap = dict()
    for i in range(len(nums)):
        num = nums[i]
        complement = target - num
        if complement in numsMap:
            return [numsMap[complement], i]
        else:
            numsMap[num] = i
    return []
```