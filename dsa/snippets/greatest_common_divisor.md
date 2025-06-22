```python
def greatestCommonDivisor(num1, num2):
    a = num1
    b = num2
    while True:
        if a == 0:
            return b
        if b == 0:
          return a
        a, b = b, a%b
```

### use cases

- divisor during calculation slope of line connecting two or more pointers on a graph
