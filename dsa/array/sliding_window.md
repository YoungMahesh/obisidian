You are given string `str1` and an integer `k`. Your task is to find the length of the largest sustring with at most `k` distinct characters

```python
# sliding window method
    # increment endIdx until k > len(charDict)
    # once k > len(charDict), increment startIdx until len(charDict) <= k
# O(n) time, O(n) space
def kDistinctChars(k, str1):
    if k == 0 or len(str1) == 0:
        return 0

    charDict = dict()
    maxSubLen = 0
    startIdx=0; endIdx=0
    while endIdx < len(str1):
        endChar = str1[endIdx]
        if endChar in charDict:
            charDict[endChar] += 1
        else:
            charDict[endChar] = 1

        while len(charDict) > k:
            startChar = str1[startIdx]
            charDict[startChar] -= 1
            if charDict[startChar] == 0:
                del charDict[startChar]
            startIdx += 1

        maxSubLen = max(maxSubLen, endIdx-startIdx+1)
        endIdx += 1

    return maxSubLen
```