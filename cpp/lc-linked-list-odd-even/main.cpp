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
    ListNode* oddEvenList(ListNode* head) {
       ListNode sentinel_odd{ 0 }, sentinel_even{ 0 };
       ListNode *tail_odd = &sentinel_odd, *tail_even = &sentinel_even;

       size_t i = 0;
       while (head)
       {
          if (i % 2 == 0) // odd
          {
             tail_odd->next = head;
             tail_odd = head;
          }
          else
          {
             tail_even->next = head;
             tail_even = head;
          }

          i++;
          head = head->next;
       }

       tail_even->next = nullptr;
       tail_odd->next = sentinel_even.next;
       return sentinel_odd.next;
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
   ListNode* L = vector_to_list({ 1,2,3,4,5 });
   auto r = Solution().oddEvenList(L);

   CHECK(list_to_vector(r) == std::vector<int>{1, 3, 5, 2, 4});
}

TEST_CASE("example 2")
{
   ListNode* L = vector_to_list({ 2,1,3,5,6,4,7 });
   auto r = Solution().oddEvenList(L);

   CHECK(list_to_vector(r) == std::vector<int>{ 2,3,6,7,1,5,4 });
}

