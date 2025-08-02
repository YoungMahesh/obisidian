```python
# we will have 2 files - code.py (copy-paste code) and app.py (execute code)

# file1 - code.py
class Solution:
    def sum1(self, nums):
        final = sum(nums)
        return final
 

# file2 - app.py
# from file_name import class_name
from code import Solution

instance = Solution()        
result = instance.sum1([2, -2, 0, 3, -3, 5])
print(result)
```