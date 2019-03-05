#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <set>

struct ListNode {
  int val;
  ListNode *next{nullptr};

  ListNode(int x) : val(x) {}
};

// this solution creates a new list
//class Solution {
//public:
//    ListNode* mergeTwoLists(const ListNode* L1, const ListNode* L2) {
//       if (L1 == nullptr && L2 == nullptr) return nullptr;
//       if (L1 == nullptr) return cloneList(L2);
//       if (L2 == nullptr) return cloneList(L1);
//
//       if (L1->val > L2->val)
//       {
//          std::swap(L1, L2);
//       }
//       ListNode* head = new ListNode(L1->val);
//       ListNode* tail = head;
//       L1 = L1->next;
//
//       while (L1 && L2)
//       {
//          if (L1->val < L2->val)
//          {
//             tail->next = new ListNode(L1->val);
//             L1 = L1->next;
//          }
//          else
//          {
//             tail->next = new ListNode(L2->val);
//             L2 = L2->next;
//          }
//          tail = tail->next;
//       }
//       if (L1)
//       {
//          tail->next = cloneList(L1);
//       }
//       if (L2)
//       {
//          tail->next = cloneList(L2);
//       }
//
//       return head;
//    }
//
//private:
//   ListNode* cloneList(const ListNode* L)
//   {
//      ListNode* head = new ListNode(L->val);
//      ListNode* tail = head;
//      L = L->next;
//
//      while (L)
//      {
//         tail->next = new ListNode(L->val);
//         tail = tail->next;
//         L = L->next;
//      }
//
//      return head;
//   }
//};

// this solution does merging in-place
// possible improvement: use dummy head node to keep track and then return dummy.next, e.g.:
    //ListNode* mergeTwoLists(ListNode* curr1, ListNode* curr2) {
    //    ListNode dummy(INT_MIN);
    //    ListNode *curr = &dummy;
    //    while(curr1 && curr2){
    //        if(curr1->val <= curr2->val){
    //            curr -> next = curr1;
    //            curr1 = curr1-> next;
    //        }
    //        else if(curr1->val > curr2->val){
    //            curr -> next = curr2;
    //            curr2 = curr2-> next; 
    //        }
    //        curr = curr ->next;
    //    }
    //    if(curr1)
    //        curr -> next = curr1;
    //    else 
    //        curr -> next = curr2;
    //    
    //    return dummy.next;
    //}

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* L1, ListNode* L2) {
       if (L1 == nullptr) return L2;
       if (L2 == nullptr) return L1;

       if (L1->val > L2->val)
       {
          std::swap(L1, L2);
       }
       ListNode* head = L1;
       ListNode* tail = head;
       L1 = L1->next;

       while (L1 && L2)
       {
          if (L1->val < L2->val)
          {
             tail->next = L1;
             L1 = L1->next;
          }
          else
          {
             tail->next = L2;
             L2 = L2->next;
          }
          tail = tail->next;
       }

       if (L1)
       {
          tail->next = L1;
       }
       if (L2)
       {
          tail->next = L2;
       }

       return head;
    }

private:
   ListNode* cloneList(const ListNode* L)
   {
      ListNode* head = new ListNode(L->val);
      ListNode* tail = head;
      L = L->next;

      while (L)
      {
         tail->next = new ListNode(L->val);
         tail = tail->next;
         L = L->next;
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

TEST_CASE("Example null 1")
{
   Solution solution;
   CHECK(solution.mergeTwoLists(nullptr, nullptr) == nullptr);
}

TEST_CASE("Example null 2")
{
   Solution solution;
   auto r = solution.mergeTwoLists(nullptr, vector_to_list({ 1 }));
   CHECK(list_to_vector(r) == std::vector<int>{1});
}

TEST_CASE("Example null 3")
{
   Solution solution;
   auto r = solution.mergeTwoLists(vector_to_list({ 1 }), nullptr);
   CHECK(list_to_vector(r) == std::vector<int>{1});
}

TEST_CASE("Example 1")
{
   Solution solution;
   auto r = solution.mergeTwoLists(vector_to_list({ 1,2,4 }), vector_to_list({ 1,3,4 }));
   CHECK(list_to_vector(r) == std::vector<int>{1, 1, 2, 3, 4, 4});
}

