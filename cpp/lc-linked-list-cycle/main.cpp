// https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/773/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <set>

struct ListNode {
  int val;
  ListNode *next{nullptr};

  ListNode(int x) : val(x) {}
};

class Solution {
public:

  bool hasCycle(const ListNode *head) {
    if(head == nullptr) return false;

    const auto move_hare = [](const ListNode* cur) -> const ListNode*
    {
      if(cur->next) return cur->next->next;
      return nullptr;
    };

    const ListNode *hare, *turtle;
    hare = turtle = head;
    hare = move_hare(hare);
    turtle = turtle->next;
    while(hare && turtle && hare != turtle)
    {
      hare = move_hare(hare);
      turtle = turtle->next;
    }

    return hare && turtle && hare == turtle;
  }
};
