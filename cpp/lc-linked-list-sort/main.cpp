#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

struct ListNode {
   int val;
   ListNode *next{ nullptr };
   ListNode(int x) : val(x) {}
};

class Solution {
public:
   ListNode* sortList(ListNode* head)
   {
      if (!head || !head->next)
      {
         return head;
      }

      ListNode* tail = head;
      ListNode* middle_prev = nullptr;
      ListNode* middle = head;

      while (tail)
      {
         middle_prev = middle;
         middle = middle->next;

         tail = tail->next;
         if (tail)
         {
            tail = tail->next;
         }
      }
      middle_prev->next = nullptr;

      ListNode* first_half = sortList(head);
      ListNode* second_half = sortList(middle);

      ListNode sentinel(-1);
      {
         ListNode* curr1 = first_half;
         ListNode* curr2 = second_half;
         {
            ListNode* curr = &sentinel;

            while (curr1 && curr2) {
               if (curr1->val <= curr2->val) {
                  curr->next = curr1;
                  curr1 = curr1->next;
               }
               else if (curr1->val > curr2->val) {
                  curr->next = curr2;
                  curr2 = curr2->next;
               }
               curr = curr->next;
            }
            if (curr1)
               curr->next = curr1;
            else
               curr->next = curr2;
         }
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

TEST_CASE("example")
{
   {
      auto r = Solution().sortList(vector_to_list({ 1 }));
      CHECK(list_to_vector(r) == std::vector<int>{1});
   }
   {
      auto r = Solution().sortList(vector_to_list({ 2,1 }));
      CHECK(list_to_vector(r) == std::vector<int>{1, 2});
   }
   {
      auto r = Solution().sortList(vector_to_list({ 2,1,3 }));
      CHECK(list_to_vector(r) == std::vector<int>{1, 2, 3});
   }
   {
      auto r = Solution().sortList(vector_to_list({ 4,2,1,3 }));
      CHECK(list_to_vector(r) == std::vector<int>{1, 2, 3, 4});
   }
   {
      auto r = Solution().sortList(vector_to_list({ -1,5,3,4,0 }));
      CHECK(list_to_vector(r) == std::vector<int>{-1, 0, 3, 4, 5});
   }
}

