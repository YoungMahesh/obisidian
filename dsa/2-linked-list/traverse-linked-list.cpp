#include <vector>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() {
    val = 0;
    next = nullptr;
  }
  ListNode(int data1) {
    val = data1;
    next = nullptr;
  }
  ListNode(int data1, ListNode *next1) {
    val = data1;
    next = next1;
  }
};

class Solution {
public:
  vector<int> LLTraversal(ListNode *head) {
    vector<int> result;
    ListNode *currNode = head;
    while (currNode != nullptr) {
      result.push_back(currNode->val);
      currNode = currNode->next;
    }
    return result;
  }
};
