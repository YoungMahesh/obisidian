```py
def permute(nums):
    if len(nums) == 1:
        return nums
    
    final = []

    for _ in range(len(nums)):
        removed = nums.pop(0)  # remove first element from nums array

        # generate all possible permutations of the remaining elements
        perms = permute(nums)

        for p in perms:
            p.append(removed)  # append previously removed element 
        
        final.extend(perms)

        # restore the nums length
        nums.append(removed)

    return final
```

```txt
permute([1,2,3])
    loop0
        removed=1, nums=[2,3] 
        perms = permute(nums=[2,3])
            loop0
                removed=2, nums = [3]
                perms = permute([3]) => [[3]]
                    return [3]
                
                perms = [[3,2]]  # for p in perms
                nums=[3,2]
            loop1
                removed=3, nums=[2]
    loop1
    loop2
```


```python
# O(n*n!) time, O(n*n!) space
def getPermutations(array):
    if len(array) == 0:
        return []
    permutations = []
    collectPermutations(array, 0, permutations)
    return permutations


def collectPermutations(array, i, permutations):
    if i == len(array):
        permutations.append(array[:]) # copy and append 
        return

    for j in range(i, len(array)):
        array[i], array[j] = array[j], array[i]  # swap positions
        collectPermutations(array, i+1, permutations)
        array[i], array[j] = array[j], array[i] # original positions
```


```

```

