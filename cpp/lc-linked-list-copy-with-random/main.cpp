#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <map>

class Node {
public:
   int val{ 0 };
   Node* next{ nullptr };
   Node* random{ nullptr };

   Node() = default;
   Node(int _val, Node* _next, Node* _random)
   {
      val = _val;
      next = _next;
      random = _random;
   }
};

class Solution {
public:
   Node* copyRandomList(Node* head)
   {
      std::map<Node*, Node*> old_to_new;

      Node* sentinel = new Node(-1, nullptr, nullptr);
      {
         Node* tail = sentinel;
         Node* old_tail = head;
         while (old_tail)
         {
            tail->next = new Node(old_tail->val, nullptr, old_tail->random);
            tail = tail->next;

            old_to_new.emplace(old_tail, tail);

            old_tail = old_tail->next;
         }
      }

      {
         Node* tail = sentinel->next;
         while (tail)
         {
            if (tail->random)
            {
               tail->random = old_to_new.at(tail->random);
            }
            else
            {
               tail->random = nullptr;
            }
            
            tail = tail->next;
         }
      }

      Node* new_head = sentinel->next;
      delete sentinel;

      return new_head;
   }
};

TEST_CASE("example 1")
{
   Node* head = new Node(1, nullptr, nullptr);
   head->next = new Node(2, nullptr, nullptr);
   head->random = head->next;
   head->next->random = head->next;

   Node* new_head = Solution().copyRandomList(head);
   CHECK(new_head->val == 1);
   CHECK(new_head->random == new_head->next);
   REQUIRE_FALSE(new_head->next == nullptr);
   CHECK(new_head->next->val == 2);
   CHECK(new_head->next->random == new_head->next);
   CHECK(new_head->next->next == nullptr);
}

