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
  bool isPalindrome(ListNode* head) {
    if(head == nullptr) return true;

    // assume that the size of the linked list is at least 2
    auto reverse_list = [](ListNode* head, ListNode* tail)
    {
      auto cur = head;
      auto next = cur->next;
      head->next = nullptr;
      while(cur != tail)
      {
        auto next_next = next->next;
        next->next = cur;
        cur = next;
        next = next_next;
      }
    };

    auto list_equal = [](ListNode* L1, ListNode* L2)
    {
      while(L1 && L2)
      {
        if(L1->val != L2->val) return false;
        L1 = L1->next;
        L2 = L2->next;
      }

      return L1 == L2 && L2 == nullptr;
    };

    size_t n = 1;
    auto tail = head;
    while(tail->next)
    {
      n++;
      tail = tail->next;
    }

    if(n == 1){ return true; }
    if(n == 2){ return head->val == head->next->val; }
    if(n == 3){ return head->val == head->next->next->val; }

    // assume n >= 4
    ListNode* mid_first = nullptr;
    ListNode* mid_second = head;
    {
      for(size_t i=0;i<n/2;i++)
      {
        mid_first = mid_second;
        mid_second = mid_second->next;
      }
    }

    reverse_list(head, mid_first);
    bool is_equal = false;
    if(n % 2 == 0)
    {
      is_equal = list_equal(mid_first, mid_second);
    }
    else
    {
      is_equal = list_equal(mid_first, mid_second->next);
    }
    reverse_list(mid_first, head);
    mid_first->next = mid_second;

    return is_equal;
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

TEST_CASE("example 1")
{
  CHECK(Solution().isPalindrome(vector_to_list({1,2})) == false);
}

TEST_CASE("example 2")
{
  CHECK(Solution().isPalindrome(vector_to_list({1,2,2,1})) == true);
}

TEST_CASE("example 3")
{
  CHECK(Solution().isPalindrome(vector_to_list({1})) == true);
}

TEST_CASE("example 4")
{
  CHECK(Solution().isPalindrome(vector_to_list({})) == true);
}

TEST_CASE("example 5")
{
  CHECK(Solution().isPalindrome(vector_to_list({1,2,3,1})) == false);
}

TEST_CASE("example 6")
{
  CHECK(Solution().isPalindrome(vector_to_list({1,2,3,2,1})) == true);
}
