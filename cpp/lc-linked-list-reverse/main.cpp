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
    ListNode* reverseList(ListNode* head) {
       if (head == nullptr) return nullptr;

       ListNode* new_head = head->next;
       if (new_head != nullptr)
       {
          head->next = nullptr;
       }
       while (new_head != nullptr)
       {
          ListNode* next_head = new_head->next;
          new_head->next = head;

          head = new_head;
          new_head = next_head;
       }

       return head;
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

TEST_CASE("Example null")
{
   Solution solution;
   CHECK(solution.reverseList(nullptr) == nullptr);
}

TEST_CASE("Example 1")
{
   Solution solution;
   CHECK(list_to_vector(solution.reverseList(vector_to_list(std::vector<int>{ 1 }))) == std::vector<int>{1});
}

TEST_CASE("Example 2")
{
   Solution solution;
   CHECK(list_to_vector(solution.reverseList(vector_to_list(std::vector<int>{ 1,2,3,4,5 }))) == std::vector<int>{5,4,3,2,1});
}

