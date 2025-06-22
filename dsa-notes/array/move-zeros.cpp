#include <vector>
using namespace std;

class Solution {
public:
  void moveZeroes(vector<int> &nums) {
    int zeroCount = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == 0) {
        zeroCount += 1;
      } else {
        nums[i - zeroCount] = nums[i];
      }
    }

    int lastIdx = nums.size() - 1;
    while (zeroCount > 0) {
      nums[lastIdx] = 0;
      lastIdx -= 1;
      zeroCount -= 1;
    }
  }
};
