#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// https://leetcode.com/problems/max-number-of-k-sum-pairs
class Solution {
public:
  int maxOperations(vector<int> &nums, int k) {

    int pairsFound = 0;
    unordered_map<int, int> map1;
    for (int num : nums) {
      // by default every integer value is zero
      if (map1[num] > 0)
        map1[num] += 1;
      else
        map1[num] = 1;
    }

    for (int i = 0; i < nums.size(); i++) {
      int num = nums[i];
      if (map1[num] == 0)
        continue;
      int diff = k - num;
      if (map1[diff] == 0)
        continue;

      bool areSame = num == diff;
      if (areSame) {
        if (map1[diff] >= 2) {
          map1[diff] -= 2;
          pairsFound += 1;
        }
      } else {
        map1[num] -= 1;
        map1[diff] -= 1;
        pairsFound += 1;
      }
    }

    return pairsFound;
  }
};

int main() {
  Solution solution;
  vector<int> a{3, 1, 3, 4, 3};
  int pairs = solution.maxOperations(a, 6);
  cout << "pairs: " << pairs << endl;
}
