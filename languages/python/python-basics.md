
### characters, numbers, strings, types
```python
#---------------------------characters--------------------------------
char = 'A'
ascii_value = ord(char)
ascii_value = 65

# integer to character
char = chr(ascii_value)

# characters to integers
ord('a') == 97, ord('z') == 122
ord('A') == 65, ord('Z') == 90

if 'a' in 'abcede':
    pass

# -------------- verify type ---------------
type(10) == type(x) 

#---------------------------numbers---------------------------------
int('40')       # returns integer
float('40.23')  # returns float-number
str(35)        # "35", converted to string
str(43.34)     # "44.34"

largest_number = float('inf')
smallet_number = float('-inf') 

import math
math.floor(35.80) # 35
math.ceil(40.43) # 41
round(53.7) # 54

from random import randint
# get random number from min_val to max_val, both min_val and max_val included
randint(min_val, max_val) 

# ------------------------- strings ----------------------------------
# convert uppercase, lowercase
word.upper()  # returns word with all characters as uppercase
word.lower()  # return word with all characters lowercase
# original word remains same

word.strip()   # remove left and right whitespaces

name = 'Shivaji'   # declaration
name += " Maharaj" # Shivaji Maharaj
name = ' ' * 15    # name == 15-blankspaces

delimiter = ',';
name.split(delimiter)    # split string at each comma delimiter, delimiter can be ' ', ',', 'a', etc
name = delimiter.join(str_arr)  # join elements of string_arr using delimiter, 
nums = delimiter.join(map(str, number_list)) # join numbers_array to form a string 
```
### for loop
```python
# iterate through each element in array
for num in nums:
    print(num)

# iterate through index of array
for i in range(0, len(nums)):
    print(nums[i])
 
# reverse iterate through index of array (from index len(nums)-1 to 0)
for i in range(len(nums)-1, -1, -1):
    print(nums[i])
```