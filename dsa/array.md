###  non-constructible change
We are given an array of positive integers, which represent the values of coins that we have in our possession. The array could have duplicates. We are asked to write a function that returns the minimum amount of change that we cannot create with our coins. For instance, if the input array is `[1, 2, 5]`, the minimum amount of change that we cannot create is `4`, since we can create `1`, `2`, `3 (1 + 2)` and `5`.
```python
# brute force approach
# iterate from 1 to sumOfAllCoins
    # check if you can create change for this amount
    # if not return it
# return sumOfAllCoins+1

# optimal approach
# sort array
# iterate through sorted-coin-array
    # if encounter an amount > prevPossibleChange + 1
        # return prevPossibleChange+1

# theory: if we get any amount <= prevPossibleChange+1, then we can always create all changes
    # until prevPossibleChange + currAmount
    # e.g. 1,2,3,4 -> when we iterate until 3, we get all possible changes until 6
    # now, if we got 4 -> then we got changes for -> (4+1=5),(4+2=6),(4+3=7),(4+3+1=8)
    # (4+3+2=9), (4+3+2+1=10)
# return lastChange+1+1
# check if we can create change for amount provided: sortedArrOfCoins, amount
# check all possible combination of coins with value from 1 to amount
# use recursion - at every step, you either choose coin or not choose coiny

def nonConstructibleChange(coins):
    if len(coins) == 0:
        return 1
    coins.sort()
    if coins[0] != 1:
        return 1
    
    canChange = 1
    for i in range(1, len(coins)):
        currCoin = coins[i]
        if currCoin > canChange+1:
            return canChange+1
        canChange += currCoin
        
    return canChange+1
```

