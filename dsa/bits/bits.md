

# Bit Representation
In computing, a bit (short for binary digit) is the basic unit of information and can have only one of the two values: 0 or 1.
Bits are often grouped together to represent larger units of information. For example, a group of 8 bits is byte.


## bitwize operators
```
Binary   AND    &
Binary   OR     |
Binary   XOR    ^
Binary   NOT    ~
Binary   Left shift    <<
Binary   Right shift   >>
```

### XOR (exclusive OR)
1 if bits are different, otherwise 0
```
0 ^ 0 = 0
0 ^ 1 = 1
1 ^ 0 = 1
1 ^ 1 = 0
```

### NOT
flips each bit of the operand, turning 0s to 1s and 1s into 0s
`~1010` => `0101`

### Left Shift
shifts bits of the left operand to the left by the a number of positions specified by the right operand
`1010<<2` => `101000`

### Right Shift
shifts bits of the left operand to the right by a number of positions specified by the right operand
`1010>>2` => `0010`

### AND
1 if both bits are 1, otherwise 0
```
0 & 0 = 0
0 & 1 = 0
1 & 0 = 0
1 & 1 = 1
```

### OR
1 if atleast on of the bits is 1, otherwise 0
```
0 | 0 = 0
0 | 1 = 1
1 | 0 = 1
1 | 1 = 1
```




## number systems 

### binary number system
Binary number system is a base-2 numeral system, which means that uses only two digits: 0 and 1.
Each number in binary number is called a bit.

### positional notation
similar to decimal system where, where each digit's position represents a power of 10, in binary, each digit's position represents power of 2.

for example:
- in the decimal number 235, the digit '5' represents 5x10^0, digit '3' represents 3x10^1, digit '2' represents 2x10^2
- in the binary number 1101, the rightmost digit '1' represents 1x2^0, the next digit '0' represents 1x2^1,
the next '1' represents 1x2^2, the the leftmost '1' represents 1x2^3

## representation of numbers
Representing a number in bits involves expressing that number using only 0s and 1s in binary form.
Each digit in a binary number represents  a power of 2, starting from the rightmost digit.

Example: To represent 13 in binary, we need to find which powers of 2 sum up to 13. 

Starting from the largest power of 2 less than or equal to 13, we find that 2^3 = **8** is the largest power of 2 less than 13.
Substracting 8 from 13 we get 5.
Next, the largest power of 2 less than or equal to 5 is 2^2 = **4**, leaving 1.
Finally, the largest power of 2 less or equal to 1 is 2^0 = **1**.

So we have 13 = 8 + 4 + 1

Thus 13 is represented in bits as 1101



### sum of two numbers in binary-form (0 or 1)

```python
def calculate(digitA, digitB, carry):
    currSum = int(digitA) + int(digitB) + carry
    print('currSum', currSum)
    if currSum == 3:
        return '1', 1
    elif currSum == 2:
        return '0', 1
    elif currSum == 1:
        return '1', 0
    return '0', 0
sumDigit, carry = calcualte('0', '1', 0)
```



