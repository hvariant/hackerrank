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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
       size_t i = 0;
       ListNode* cur = head;
       while (i < n && cur)
       {
          i++;
          cur = cur->next;
       }

       if (cur == nullptr) // length of list is shorter or equal to n
       {
          if (i == n) // removing the first node
          {
             cur = head->next;
             delete head;
             return cur;
          }

          return head;
       }
       else
       {
          ListNode* nth_prior_prev = nullptr;
          ListNode* nth_prior = head;
          while (cur)
          {
             nth_prior_prev = nth_prior;
             nth_prior = nth_prior->next;
             cur = cur->next;
          }

          nth_prior_prev->next = nth_prior->next;
          delete nth_prior;

          return head;
       }
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

TEST_CASE("example 1")
{
   CHECK(list_to_vector(
      Solution().removeNthFromEnd(vector_to_list({ 1,2,3,4,5 }), 2)
   ) == std::vector<int>{1, 2, 3, 5});
}

TEST_CASE("example 2")
{
   CHECK(list_to_vector(
      Solution().removeNthFromEnd(vector_to_list({ 1,2,3,4,5 }), 5)
   ) == std::vector<int>{2, 3, 4, 5});
}

TEST_CASE("example 3")
{
   CHECK(list_to_vector(
      Solution().removeNthFromEnd(vector_to_list({ 1,2,3,4,5 }), 1)
   ) == std::vector<int>{1, 2, 3, 4});
}

TEST_CASE("example 4")
{
   CHECK(list_to_vector(
      Solution().removeNthFromEnd(vector_to_list({ 1,2,3,4,5 }), 6)
   ) == std::vector<int>{1, 2, 3, 4, 5});
}
