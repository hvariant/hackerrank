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
   ListNode* addTwoNumbers(const ListNode* l1, const ListNode* l2) {
      // assert l1 && l2

      auto sentinel = ListNode{ 0 };
      ListNode* tail = &sentinel;

      int carry = 0;
      const ListNode *ptr1 = l1, *ptr2 = l2;
      while (ptr1 || ptr2)
      {
         int digit1 = ptr1 ? ptr1->val : 0;
         int digit2 = ptr2 ? ptr2->val : 0;

         int r = digit1 + digit2 + carry;
         tail->next = new ListNode{ r % 10 };
         carry = r / 10;

         tail = tail->next;
         ptr1 = ptr1 ? ptr1->next : nullptr;
         ptr2 = ptr2 ? ptr2->next : nullptr;
      }
      if (carry > 0)
      {
         tail->next = new ListNode{ carry };
      }

      return sentinel.next;
   }
};

ListNode* vector_to_list(const std::vector<int>& v)
{
  if(v.empty()) return nullptr;

  ListNode* head = new ListNode(v[0]);
  ListNode* tail = head;
  for(size_t i=1;i<v.size();i++)
  {
    auto n = v[i];
    tail->next = new ListNode(n);
    tail = tail->next;
  }
  return head;
}

std::vector<int> list_to_vector(ListNode* head)
{
   std::vector<int> v;
   while (head)
   {
      v.push_back(head->val);
      head = head->next;
   }
   return v;
}

TEST_CASE("example null 1")
{
   ListNode* L1 = vector_to_list({ 0 });
   ListNode* L2 = vector_to_list({ 5,6,4 });
   auto r = Solution().addTwoNumbers(L1, L2);

   CHECK(list_to_vector(r) == std::vector<int>{5, 6, 4});
}

TEST_CASE("example null 2")
{
   ListNode* L1 = vector_to_list({ 0 });
   ListNode* L2 = vector_to_list({ 0 });
   auto r = Solution().addTwoNumbers(L1, L2);

   CHECK(list_to_vector(r) == std::vector<int>{ 0 });
}

TEST_CASE("example 1")
{
   ListNode* L1 = vector_to_list({ 2,4,3 });
   ListNode* L2 = vector_to_list({ 5,6,4 });
   auto r = Solution().addTwoNumbers(L1, L2);

   CHECK(list_to_vector(r) == std::vector<int>{7, 0, 8});
}
