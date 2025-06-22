Write a function that takes in a string made up of parentheses `(` and `)` . The function should return an integer representing the length of the longest balanced substring with regards to parenthesis
```python
# brute force
# 1. find out every substring
# 2. check if it is valid balanced string
# 3. keep track of maxLen of balanced string
# O(n^3) time, O(1) space

def longestBalancedSubstring(string):

    maxLen = 0
    for i in range(len(string)-1):
        for j in range(i+1, len(string), 2):
            # balaned string will always have even length, hence we are incrementing
                # endIdx by 2 at each step
            currLen = findLenOfBalancedStr(string, i, j)
            maxLen = max(maxLen, currLen)

    return maxLen


def findLenOfBalancedStr(string, startIdx, endIdx):
    openBracketsCount = 0
    for i in range(startIdx, endIdx+1):
        if string[i] == '(':
            openBracketsCount += 1
        else:
            if openBracketsCount > 0:
                openBracketsCount -= 1
            else:
                return 0

    return endIdx+1 - startIdx if openBracketsCount == 0 else 0
```

```python
# store indices of extra open-brackets and close-brackets in stack
# by looking at the top-index in stack and current-index we can find out
    # length of balanced substring

# O(n) time, O(n) space
def longestBalancedSubstring(string):
    stack = [-1]
    maxLen = 0
    for i in range(len(string)):
        if string[i] == '(':
            stack.append(i)
        else:
            stack.pop()
            if len(stack) == 0:
                stack.append(i)
            else:
                balSubStringStart = stack[-1]
                currLen = i - balSubStringStart
                maxLen = max(maxLen, currLen)
    return maxLen
    
```