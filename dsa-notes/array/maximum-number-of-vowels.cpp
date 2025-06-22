// #include <iostream>
#include <string>
#include <unordered_map>
// #include <vector>
using namespace std;

// https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/
class Solution {
public:
  int maxVowels(string s, int k) {
    unordered_map<char, bool> vowels;
    for (char v : "aeiou") {
      vowels[v] = true;
    }

    int maxVCount = 0;
    int currVCount = 0;

    // vowels count in first substring
    for (int i = 0; i < k; i++) {
      char currChar = s[i];
      if (vowels[currChar])
        currVCount += 1;
    }
    maxVCount = currVCount;

    // vowels count in remaining substrings
    for (int i = k; i < s.size(); i++) {
      char firstChar = s[i - k];
      char nextChar = s[i];

      if (vowels[firstChar])
        currVCount -= 1;
      if (vowels[nextChar])
        currVCount += 1;

      maxVCount = max(maxVCount, currVCount);
    }

    return maxVCount;
  }
};
