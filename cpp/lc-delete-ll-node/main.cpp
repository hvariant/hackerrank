// https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/553/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

struct ListNode {
  int val;
  ListNode *next{nullptr};
  ListNode(int x) : val(x) {}
};

class Solution {
public:
  void deleteNode(ListNode* node) {
    ListNode* prev = nullptr;
    while(node->next)
    {
      prev = node;
      node->val = node->next->val;
      node = node->next;
    }
    prev->next = nullptr;
  }
};

