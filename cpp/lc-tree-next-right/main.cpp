#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <queue>

namespace
{
  struct Node {
    int val;
    Node *left{nullptr};
    Node *right{nullptr};
    Node *next{nullptr};

    Node(int x) : val(x) {}
  };
}

class Solution {
public:
  Node* connect(Node* root) {
    if(root == nullptr) return nullptr;

    std::queue<Node*> Q;
    Q.push(root);

    while(!Q.empty())
    {
      Node* cur = Q.front();
      Q.pop();

      if(cur->left != nullptr && cur->right != nullptr)
      {
        cur->left->next = cur->right;
        if(cur->next != nullptr)
        {
          cur->right->next = cur->next->left;
        }

        Q.push(cur->left);
        Q.push(cur->right);
      }
    }

    return root;
  }
};

bool tree_equal(Node* T1, Node* T2)
{
  if(T1 == nullptr || T2 == nullptr)
  {
    return T1 == T2;
  }

  if(T1->val != T2->val)
  {
    return false;
  }

  if(T1->next == nullptr || T2->next == nullptr)
  {
    if(T1->next != T2->next)
    {
      return false;
    }
  }
  else if(T1->next->val != T2->next->val)
  {
    return false;
  }

  return tree_equal(T1->left, T2->left) && tree_equal(T1->right, T2->right);
}

TEST_CASE("null 1")
{
  auto output = new Node{1};

  auto expected = new Node{1};

  output = Solution().connect(output);
  CHECK(tree_equal(output, expected));
}

TEST_CASE("example 1")
{
  auto output = new Node{1};
  output->left = new Node{2};
  output->left->left = new Node{4};
  output->left->right = new Node{5};
  output->right = new Node{3};
  output->right->left = new Node{6};
  output->right->right = new Node{7};

  auto expected = new Node{1};
  expected->left = new Node{2};
  expected->left->left = new Node{4};
  expected->left->right = new Node{5};
  expected->right = new Node{3};
  expected->right->left = new Node{6};
  expected->right->right = new Node{7};

  expected->left->next = expected->right;
  expected->left->left->next = expected->left->right;
  expected->left->right->next = expected->right->left;
  expected->right->left->next = expected->right->right;

  output = Solution().connect(output);
  CHECK(tree_equal(output, expected));
}
