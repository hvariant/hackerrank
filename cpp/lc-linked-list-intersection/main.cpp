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
   // an explanation of this algorithm:
   // say you have these two linked lists:
   //            o v
   //                # -> # -> #
   //  0 -> 0 -> 0 ^
   //
   // by moving curA to headB and curB to headA,
   // what is happening is that the parts before the common suffix are effectively stitched together, i.e.:
   // 
   //  0 -> 0 -> 0 -> o v
   //                   # -> # -> #
   //  o -> 0 -> 0 -> 0 ^
   //
   // which makes the two prefix parts have the same length, therefore A and B will arrive at the first node of
   // the common suffix at the same time.
   //
   // It is trivial to see that when there is no common suffix, curA == curB == nullptr.
   // The proof is left as exercise to the reader.

   ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {
      auto curA = headA;
      auto curB = headB;

      while (curA != curB)
      {
         curA = (curA == nullptr) ? headB : curA->next;
         curB = (curB == nullptr) ? headA : curB->next;
      }

      return curA;
   }
};
