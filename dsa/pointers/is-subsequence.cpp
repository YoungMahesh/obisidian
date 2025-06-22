#include <vector>
#include <string>
using namespace std;

// https://leetcode.com/problems/is-subsequence
class Solution {
public:
  bool isSubsequence(string s, string t) {
    if (s.size() == 0)
      return true;
    if (s.size() > t.size())
      return false;

    int pointer = 0;
    for (char c : t) {
      if (c == s[pointer])
        pointer += 1;

      if (pointer == s.size())
        return true;
    }

    return false;
  }
};
