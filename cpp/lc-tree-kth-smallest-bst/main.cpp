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

#include <unordered_map>

class Solution {
public:
   int kthSmallest(TreeNode* root, int k) {
      std::unordered_map<TreeNode*, size_t> family_count;
      (void)countFamily(root, family_count);
      family_count[nullptr] = 0;

      return _kthSmallest(root, k, family_count);
   }
private:
   int _kthSmallest(TreeNode* root, int k, std::unordered_map<TreeNode*, size_t>& family_count)
   {
      if (k == 1)
      {
         while (root->left)
         {
            root = root->left;
         }
         return root->val;
      }

      if (family_count[root->left] + 1 < k)
      {
         return _kthSmallest(root->right, k - family_count[root->left] - 1, family_count);
      }
      else if (family_count[root->left] + 1 == k)
      {
         return root->val;
      }
      else
      {
         return _kthSmallest(root->left, k, family_count);
      }
   }

   size_t countFamily(TreeNode* root, std::unordered_map<TreeNode*, size_t>& family_count)
   {
      if (root == nullptr)
      {
         return 0;
      }
      if (family_count.count(root) > 0)
      {
         return family_count[root];
      }

      size_t left_children_count = countFamily(root->left, family_count);
      size_t right_children_count = countFamily(root->right, family_count);

      family_count[root] = left_children_count + right_children_count + 1;
      return family_count[root];
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
