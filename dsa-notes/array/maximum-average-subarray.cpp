// #include <iostream>
// #include <unordered_map>
#include <vector>
using namespace std;

// https://leetcode.com/problems/maximum-average-subarray-i

class Solution {
public:
  double findMaxAverage(vector<int> &nums, int k) {

    double maxAvg = 0;
    double currSum = 0;

    // average through first k elements
    for (int i = 0; i < k; i++) {
      currSum += nums[i];
    }
    maxAvg = currSum / k;

    // max average
    for (int i = k; i < nums.size(); i++) {
      // add one element after current last, remove one element from the current

      // remove one from left side
      currSum -= nums[i - k];

      // add one from right side
      currSum += nums[i];

      double currAvg = currSum / k;
      maxAvg = max(maxAvg, currAvg);
    }

    return maxAvg;
  }
};

// int main() {
//   Solution solution;
//   vector<int> a{3, 1, 3, 4, 3};
//   int pairs = solution.maxOperations(a, 6);
//   cout << "pairs: " << pairs << endl;
// }
