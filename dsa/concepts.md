## euclidean algorithms
- an efficient method for findng the greatest common divisor (GCD) of two positive integers.
- the GCD is the largest number that divides both integers without leaving a remainder.

### basic principle
- Basic Principle: The algorithm is based on the observation that the GCD of two numbers remains same if the larger number is replaced by its difference with smaller number
  ```
  gcd(a,b) = gcd(b, a%b)
  ```
- Example: Let's find the GCD of 210 and 45:
  ```
  1. 210/45 = 4 with a remainder of 30
  2. 45/30 = 1 with a remainder of 15
  3. 30/15 = 2 with a remainder of 0
  Here, the remainder becomes zero in the third setp. Therefore, the GCD of 210 and 45 is 15.
  ```
  
