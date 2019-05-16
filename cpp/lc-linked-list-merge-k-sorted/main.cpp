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

class Solution {
public:
   ListNode* mergeKLists(const std::vector<ListNode*>& lists) {
      ListNode* sentinel = new ListNode(-1);
      ListNode* tail = sentinel;

      std::vector<ListNode*> heads = lists;
      while (true)
      {
         std::optional<size_t> min_val_index_opt;
         for (size_t i = 0; i < heads.size(); i++)
         {
            if (heads[i])
            {
               if (!min_val_index_opt.has_value()
                  ||
                  (min_val_index_opt.has_value() && heads[*min_val_index_opt]->val > heads[i]->val))
               {
                  min_val_index_opt = i;
               }
            }
         }
         if (!min_val_index_opt.has_value())
         {
            break;
         }

         size_t index = min_val_index_opt.value();
         tail->next = new ListNode(heads[index]->val);

         tail = tail->next;
         heads[index] = heads[index]->next;
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

