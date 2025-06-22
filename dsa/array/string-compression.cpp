#include <iostream>
#include <vector>
using namespace std;

//https://leetcode.com/problems/string-compression
class Solution {

  vector<char> numberToChars(int num) {
    vector<char> v1;
    while (num > 0) {
      int lastDigit = num % 10;
      v1.push_back('0' + lastDigit);
      num = num / 10;
    }

    int i = 0;
    int j = v1.size() - 1;
    while (i < j) {
      char temp = v1[j];
      v1[j] = v1[i];
      v1[i] = temp;
			i += 1;
			j -= 1;
    }

    return v1;
  }

public:
  int compress(vector<char> &chars) {

    int counter = 1;
    char latestChar = chars[0];
    int emptyPositionPointer = 1;
    for (int i = 1; i < chars.size(); i++) {
      if (latestChar == chars[i]) {
        counter += 1;
      } else {
        if (counter >= 2) { // counter becomes 2 or more digits
          vector<char> counterToDigits = numberToChars(counter);
          for (int k = 0; k < counterToDigits.size(); k++) {
            chars[emptyPositionPointer] = counterToDigits[k];
            emptyPositionPointer += 1;
          }
        }
        chars[emptyPositionPointer] = chars[i];
        emptyPositionPointer += 1;
        latestChar = chars[i];
        counter = 1;
      }
    }

    if (counter >= 2) { // counter becomes 2 or more digits
      vector<char> counterToDigits = numberToChars(counter);
      for (int k = 0; k < counterToDigits.size(); k++) {
        chars[emptyPositionPointer] = counterToDigits[k];
        emptyPositionPointer += 1;
      }
    }
    return emptyPositionPointer;
  }
};

int main() {
  Solution solution;
  vector<char> arr1{'a', 'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'c'};
  cout << solution.compress(arr1) << endl;
}

// c:1
// a b <
// 3

// a","2","b","2","c","3","c"
// 0   1   2   3   4   5   6
//                            i
//                 p
// counter = 3
// lastChar = c
// latestCharPos = 0
