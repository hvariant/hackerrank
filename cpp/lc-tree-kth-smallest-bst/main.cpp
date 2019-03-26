#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

namespace
{
  struct TreeNode {
    int val;
    TreeNode *left{nullptr};
    TreeNode *right{nullptr};

    TreeNode(int x) : val(x) {}
  };
}

class Solution {
public:
   int kthSmallest(TreeNode* root, int k)
   {
      return _kthSmallest(root, k);
   }

private:
   int _kthSmallest(TreeNode* root, int& k)
   {
      if (root == nullptr)
      {
         return 0;
      }

      int val = _kthSmallest(root->left, k);
      if (k == 0)
      {
         return val;
      }

      k--;
      if (k == 0)
      {
         return root->val;
      }

      return _kthSmallest(root->right, k);
   }
};

TEST_CASE("example 1")
{
  Solution solution;

  TreeNode* root = new TreeNode{3};
  root->left = new TreeNode{1};
  root->left->right = new TreeNode{2};
  root->right = new TreeNode{4};

  for (size_t i = 1; i <= 4; i++)
  {
     CHECK(solution.kthSmallest(root, i) == i);
  }
}

TEST_CASE("example 2")
{
  Solution solution;

  TreeNode* root = new TreeNode{5};
  root->left = new TreeNode{3};
  root->left->left = new TreeNode{2};
  root->left->left->left = new TreeNode{1};
  root->left->right = new TreeNode{4};
  root->right = new TreeNode{6};

  for (size_t i = 1; i <= 6; i++)
  {
     CHECK(solution.kthSmallest(root, i) == i);
  }
}
