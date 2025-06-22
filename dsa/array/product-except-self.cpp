#include <vector>
using namespace std;

// https://leetcode.com/problems/product-of-array-except-self
class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    // at any point, total-product-sum except nums[i] = left-to-right-product-sum[i-1] * right-left-product-sum[i+1]

    // 1. create vector for left-to-right product sum
    vector<int> leftToRight(nums.size(), 0);
    leftToRight[0] = nums[0];                   // according to description, minimum lenght of nums is 2, hence no need to verify if index exists
    for (int i = 1; i < nums.size() - 1; i++) { // only prefix-sum or suffix-sum can fit 32-bit integer, hence we will not iterate until last num
      leftToRight[i] = leftToRight[i - 1] * nums[i];
    }

    // 2. create vector for right-to-left product sum
    vector<int> rightToLeft(nums.size(), 0);
    int lastIdx = nums.size() - 1;
    rightToLeft[lastIdx] = nums[lastIdx];
    for (int i = lastIdx - 1; i > 0; i--) {
      rightToLeft[i] = rightToLeft[i + 1] * nums[i];
    }

    vector<int> pArray(nums.size(), 0);
    pArray[0] = rightToLeft[1];
    pArray[lastIdx] = leftToRight[lastIdx - 1];
    for (int i = 1; i < nums.size() - 1; i++) {
      pArray[i] = leftToRight[i - 1] * rightToLeft[i + 1];
    }

    return pArray;
  }
};
