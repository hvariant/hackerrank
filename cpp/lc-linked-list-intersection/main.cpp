#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_set>

struct ListNode {
  int val;
  ListNode *next{nullptr};

  ListNode(int x) : val(x) {}
};

class Solution {
public:
   ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {
      auto nodes = std::unordered_set<ListNode*>{};
      {
         auto cur = headB;
         while (cur)
         {
            nodes.insert(cur);
            cur = cur->next;
         }
      }

      {
         auto cur = headA;
         while (cur)
         {
            if (nodes.count(cur) > 0)
            {
               return cur;
            }
            cur = cur->next;
         }
      }

      return nullptr;
   }
};
