#include <iostream>
#include <string>
// #include <vector>
using namespace std;

// https://leetcode.com/problems/greatest-common-divisor-of-strings

class Solution {
public:
  bool isGCD(string &str1, string &str2, string &smaller, int endIdx) {

    // 1. is gcd of str1
    int pointer = 0;
    for (int i = 0; i < str1.size(); i++) {
      if (pointer == smaller.size()) {
        pointer = 0;
      }
      if (str1[i] != smaller[pointer])
        return false;
      pointer++;
    }
    // 2. is gcd of str2
    for (int i = 0; i < str2.size(); i++) {
      if (pointer == smaller.size())
        pointer = 0;
      if (str2[i] != smaller[pointer])
        return false;
      pointer++;
    }

    return true;
  }

  string gcdOfStrings(string str1, string str2) {
    // 1. iterate through smaller string, considering current section is gcd at each step
    string smaller = str1.size() <= str2.size() ? str1 : str2;

    int len1 = str1.size();
    int len2 = str2.size();
    int lenSmaller = smaller.size();

    for (int i = lenSmaller - 1; i >= 0; i--) {
      // 2. both strings are multiple of gcd, hence dividing gcd-length must give remainder 0
      int currLen = (i + 1) - 0;
      if (len1 % currLen != 0 || len2 % currLen != 0)
        continue;

      // 3. verify if current-section is gcd
      // as we are moving from longer-sections to smaller-sections, hence the first gcd we encouter will be largest gcd
      if (isGCD(str1, str2, smaller, i))
        return smaller.substr(0, i + 1);
    }

    // 4. no gcd found
    return "";
  }
};

int main() {
  Solution solution;
  string result1 = solution.gcdOfStrings("LEET", "CODE");
  string result2 = solution.gcdOfStrings("ABABABCD", "ABAB");
  string result3 = solution.gcdOfStrings("ABABABAB", "ABAB");
  string result4 = solution.gcdOfStrings("TAUXXTAUXXTAUXXTAUXXTAUXX", "TAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXXTAUXX");
  cout << result1 << endl;
  cout << result2 << endl;
  cout << result3 << endl;
  cout << result4 << endl;
  return 0;
}
