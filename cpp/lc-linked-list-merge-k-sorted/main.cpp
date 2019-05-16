#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

struct ListNode {
   int val;
   ListNode *next{ nullptr };
   ListNode(int x) : val(x) {}
};

#include <vector>
#include <optional>
#include <queue>

class Solution {
public:
   ListNode* mergeKLists(const std::vector<ListNode*>& lists) {
      ListNode* sentinel = new ListNode(-1);
      ListNode* tail = sentinel;

      using HeadType = std::pair<int, ListNode*>;
      auto Q = std::priority_queue<HeadType, std::vector<HeadType>, std::greater<HeadType>>{};
      for (auto head : lists)
      {
         if (head)
         {
            Q.push({ head->val, head });
         }
      }

      while (!Q.empty())
      {
         auto h = Q.top();
         Q.pop();

         tail->next = new ListNode(h.first);
         tail = tail->next;

         if (h.second->next)
         {
            auto h_next = h.second->next;
            Q.push({ h_next->val, h_next });
         }
      }

      ListNode* ret = sentinel->next;
      delete sentinel;
      return ret;
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

TEST_CASE("example")
{
   std::vector<ListNode*> input = {
      vector_to_list({1,4,5}),
      vector_to_list({1,3,4}),
      vector_to_list({2,6})
   };

   auto r = Solution().mergeKLists(input);

   CHECK(list_to_vector(r) == std::vector<int>{1, 1, 2, 3, 4, 4, 5, 6});
}

