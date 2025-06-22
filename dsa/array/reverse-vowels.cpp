#include <string>
#include <vector>
using namespace std;

// https://leetcode.com/problems/reverse-vowels-of-a-string/description/
class Solution {
public:
  bool isVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
      return true;

    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
      return true;

    return false;
  }
  string reverseVowels(string s) {

    // 1. store all vowels in a vector
    vector<char> vowels;
    for (char c : s) {
      if (isVowel(c))
        vowels.push_back(c);
    }

    // 2. put all vowels in reverse
    int vPointer = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
      if (isVowel(s[i])) {
        s[i] = vowels[vPointer];
        vPointer++;
      }
    }

    return s;
  }
};
