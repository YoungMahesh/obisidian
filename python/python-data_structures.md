## heaps

### min-heap
```python
import heapq
heapq.heapify(list1)  # convert list to min-heap
heapq.heappush(list1, 33) # insert element
ele = heapq.heappop(list1) # remove smallest element
```
### max-heap
```python
# --------------------------- 2d array ------------------------------
# elements at 0th-index is compared, if both are same,
# then 1st-index is compared, and so-on


# ------------------- grpah nodes --------------------------------------
class employee:
    def __init__(self, n, d, yos, s):
        self.name = n
        self.des = d
        self.yos = yos
        self.sal = s
  
   # override the comparison operator for less
    def __lt__(self, nxt):
        return self.yos < nxt.yos
  
# creating objects
e1 = employee('Anish', 'manager', 3, 24000)
e2 = employee('kathy', 'programmer', 2, 15000)
e3 = employee('Rina', 'Analyst', 5, 30000)
e4 = employee('Vinay', 'programmer', 1, 10000)

emp = [e1, e2, e3, e4] # list of employee objects

# as we are going to use min-heap, smallest yos will come first, largest will come last
heapq.heapify(emp) 

```


## Queue
```python
import queue

q = queue.Queue()
q.put(3)   # insert at the end
isEmpty = q.empty()
ele = q.get()    # remove and get value of first element
currSize = q.qsize()
```

## Recursion related
### set/increase recursion limt
```python
import sys
sys.setrecursionlimit(10**6)
# default recursion limit for python is 10^3 (1000), which become inadequate for large inputs
```
### cache for recursion
```python
from functools import lru_cache

# lru == least recently used
# default-size: 128, maxsize=None gives maximum available size
@lru_cache(maxsize = None)  
def helper(idx1, idx2):
    # recursive-function

# declare lru_cache on the line before recursive-function-declaration
# lru_cache adds function-parameters as keys and function-return as the value in a hash_map
```

## Set
```python
set1 = set()
set1 = {'blackberry', 'sandwitch', 'golden', 'smile'}
set1 = set(arr1) # convert array to set
len(set1)
set1.add('banana')
set1.remove('orange')

if 'apple' in set:

for ele in set1:
    print(ele)
```

## Dictionary
```python
dict0 = dict();   dict1 = {}        # declare empty hash_table
dict2 = {1: 10, 2: 20, 3: 30}		# declare hash_table with keys&values
len(dict2)        # get length of hash_table
dict3 = {key:value for key, value in dict2.items()}  # copy dictionary

dict2[4] = 200    # add key-value pair
dict3[10] = {'k': 'kamal'}
dict3[10].update({'m': 'mangal'})  # insert value, alongside with other values on the same key
dict2[(0,0)] = [3, 4, 5, 6]   # use pair of numbers as key using tuples
dict2[4]          # get value using key
dict2.pop(2, 'not found')  # delete key == 2, if key not present  then return 'not found'
if 4 in dict2     # check if 4 is present in dict2 as a key
dict2.get(47)   # None, return value if key is present else None
dict2.get(47, 2) # return 2 if key is not present


for key in a_dict:    # get all keys in dictionary
        print(a_dict[key])        # get all values in dictionary

dict2.keys()      # get all keys in the form of array
dict2.values()    # get all values in the form of array
```


## List
```python
arr1 = [1, 2, 3, 4, 5, 7, 8, 10]
arr2 = [ele for ele in arr1]  # deep copy of elements
arr3 = [idx for idx in range(len(arr1))]  # deep copy of indices

arr11 = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]]
arr12 = [[ele for ele in row1] for row1 in arr11] # deep copy of 2d array

reversedStr = string1[::-1]
reversedArr = arr1[::-1]

for index, item in enumerate(arr1):
for index, item in enumerate(string1):

numbers = [34, 11, 7, 15]
list_sorted = sorted(numbers)   # return sorted list, without affecting original list/set/tuple
# tuples, sets and dictionary can also be passed inside sorted() to get sorted-list

# ---------------- reverse sort -------------------------------
arr = sorted(arr, reverse=True)

# ---------------- two-dimensional array sort ------------------------------
arr = sorted(arr, key=lambda x: x[1])  # sort considering numbers at index 1

# --------------------- custom sort ------------------------------------
from functools import cmp_to_key
def cmpFun(a, b):
    # return 1 if want to change order, else -1
    return 1 if b[0] < a[0] else -1

arr = [[2, 34], [5, 23], [4, 244], [1, 343]]
arr2 = sorted(arr, key=cmp_to_key(cmpFun))
```