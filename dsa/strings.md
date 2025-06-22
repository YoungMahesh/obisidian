### caesar cipher encryptor

Given a non-empty string of lowercase letters and a non-negative integer representing a key, write a function that returns a new string by k positions in the alphabet, where k is the key

Note that the letters should "wrap" around the alphabet; in other words, the letter `z` shifted by one returns the letter `a`.

```input
string = 'xyz'
key = 2
```

```output
'zab'
```

```python
def caesarCipherEncryptor(str1, key):
    str2 = ""
	for letter in str1:
		num = ord(letter) - ord('a')
		num += key
		num %= 26
		num += ord('a')
		str2 += chr(num)
    return str2
```

### kmp(knuth-morris-pratt) algorithm

- find repeated group of characters / pattern in substring
  - we will try to find if our prefix matches with our suffix
  - we will move forward two pointers through substring to verify if sequence of letters are same from index_0
  - let's consider i is continuously moving forward & j moves backwards from it's current place when there is mismatch
  - if we find mismatch, j will move back to the next_element of last_pattern matched with previous_element

```python
# O(n+m) time | O(m) space, where n = len(string), m = len(substring)
def knuthMorrisPrattAlgorithm(string, substring):
    pattern = buildPattern(substring)
    return doesMatch(string, substring, pattern)

def buildPattern(substring):
    pattern = [-1 for letter in substring]

    j=0; i=1
    while i < len(substring):
        if substring[i] == substring[j]:
            pattern[i] = j
            i+=1; j+=1
        else:
            # start comparison again from previously matched pattern
            if j > 0:
                j = pattern[j-1]+1
            else:
                i+=1
    return pattern

def doesMatch(string, substring, pattern):
    i=0;j=0
    while i < len(string):
        if len(string)-i < len(substring)-j:
            return False
        if string[i] == substring[j]:
            i+=1; j+=1
            if j == len(substring):
                return True
        else:
            if j > 0:
                j = pattern[j-1]+1
            else:
                i+=1
    return False
```

```
a  e  f  a  e  d  a  e  f  a  e  f  a
0  1  2  3  4  5  6  7  8  9 10 11 12

[-1]

j=0; i=1
  sub[j] != sub[i]
  [-1, -1]
  i += 1
j=0; i=2
  sub[j] != sub[i]
  [-1,-1,-1]
  i += 1
j=0; i=3
  sub[j] == sub[i]
  [-1,-1,-1,0]  as i_char matched with j_char, we found pattern, we registering that pattern by storing j's position for i
  j+=1; i+=1
j=1; i=4
  sub[j] == sub[i]  found pattern
  [-1,-1,-1,0,1]    registered pattern
  j+=1; i+=1
j=2; i=5
  sub[j] != sub[i]


```
