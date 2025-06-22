You're given an array of points plotted on a 2D graph (the xy-plane). Wriate a function that returns the maximum number of points that a single line (or potentially multiple lines) on the graph passes through.

The input array will contain points represented by an array of two integers `[x,y]`. The input array will never contain duplicate points and will always contain atleast one point.


```python
def lineThroughPoints(points):
    maxNumberOfPointsOnLine = 1

    # if there are more than 1 points, we can draw a line through any two points
    # we will calculate slope between all point pairs, if one slope is same for
        # multiple pairs then line can be drawn from all points in that pairs
    for i in range(len(points)):
        # we will find out all slopes which include current point (p1)
        # thus we are considering all lines which contain current point (p1)
        # to avoid duplicate pairs, we are creating new slopes-dictionary during
            # each iteration
        slopes = dict()
        p1 = points[i]
        for j in range(i+1, len(points)):
            p2 = points[j]
            slopeKey = getSlopeOfLineBetweenPoints(p1, p2)
            if slopeKey not in slopes:
                # if we find new slope, we have atleast two points (p1,p2) for this slope
                slopes[slopeKey] = 2
            else:
                slopes[slopeKey] += 1

        # we are going to consider current point p1 as part of our desired line/slope
        # we are not using duplicate p1-p2 pairs, as in nested loop, we are considering
            # j = i+1
        # using default=0, in case `slopes` does not have any key-value pairs
        maxNumberOfPointsOnLine = max(maxNumberOfPointsOnLine, max(slopes.values(), default=0))
        
    # Write your code here.
    return maxNumberOfPointsOnLine


def getSlopeOfLineBetweenPoints(p1, p2):
    # slope is determined using difference between x and y axis of two points on graph
    [p1x, p1y] = p1
    [p2x, p2y] = p2

    slope = (1, 0) # default/vertical slope, [yDiff, xDiff]

    if p1x != p2x:
        yDiff = p1y - p2y
        xDiff = p1x - p2x
        # slope is a ratio of yDiff/xDiff, to find correct ratio, we need to divide
            # both values by gretest common denominator
        gcd = greatestCommonDenominator(yDiff, xDiff)
        yDiff = yDiff // gcd
        xDiff = xDiff // gcd
        # as a standard, we will not allow a negative denominator, so if denominator
            # is negative, we will pass it to numerator
        if xDiff < 0:
            xDiff *= -1
            yDiff *= -1

        slope = (yDiff, xDiff)

    return slope # using a tuple as slopeKey value as tuple is immutable

def greatestCommonDenominator(num1, num2):
    a = num1
    b = num2

    # we will reduce values of a and b, until either one of them becomes 0
    while True:
        if a == 0:
            return b
        if b == 0:
            return a
        a, b = b, a%b
```