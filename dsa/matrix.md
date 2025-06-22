### Maximum sum submatrix
You're given a two-dimensional array (a matrix) of potentially unequal height and width that's filled with intengers. You're also given a positive integer `size`.
Write a function that returns the maximum sum that can be generated from a submatrix with dimensions `size * size`.
`size` will always be at least `1`, and the dimensions of the input `matrix` will always be at least `size *size`.
```python
# O(width*height) time, O(width * height) space
def maximumSumSubmatrix(matrix, size):
    sumMatrix = getSumMatrix(matrix)
    return maxSquare(sumMatrix, matrix, size)

def maxSquare(sumMatrix, matrix, size):

    maxSquareSum = float('-inf')
    for i in range(size-1, len(matrix)):
        for j in range(size-1, len(matrix[0])):
            outerI = i-(size-1)-1; outerJ = j-(size-1)-1
            topRightRectSum = sumMatrix[outerI][j] if outerI >= 0 else 0
            topLeftRectSum = sumMatrix[outerI][outerJ] \
            if outerI >= 0 and outerJ >= 0 else 0
            bottomLeftRectSum = sumMatrix[i][outerJ] if outerJ >= 0 else 0
            currRectSum = sumMatrix[i][j]
            currSqSum = currRectSum - topRightRectSum - bottomLeftRectSum + topLeftRectSum 
            maxSquareSum = max(maxSquareSum, currSqSum)

    return maxSquareSum


def getSumMatrix(matrix):
    sumMatrix = [[ele for ele in row1] for row1 in matrix]

    # create first row 
    for i in range(1, len(matrix)):
        sumMatrix[i][0] = sumMatrix[i-1][0] + matrix[i][0]

    # create first column
    for j in range(1, len(matrix[0])):
        sumMatrix[0][j] = sumMatrix[0][j-1] + matrix[0][j]
    
    for i in range(1, len(matrix)):
        for j in range(1, len(matrix[0])):
            currSum = matrix[i][j] + sumMatrix[i-1][j] + sumMatrix[i][j-1] \
            - sumMatrix[i-1][j-1]
            sumMatrix[i][j] = currSum

    return sumMatrix 
```
