#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

struct TreeNode {
  int val;
  TreeNode *left{nullptr};
  TreeNode *right{nullptr};
  TreeNode(int x) : val(x) {}
};

class Solution {
public:
  std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> ret;

    TreeNode* current = root;
    while(current)
    {
      if(current->left == nullptr)
      {
        ret.push_back(current->val);
        current = current->right;
      }
      else
      {
        TreeNode* right_most_descendent = current->left;
        while(right_most_descendent->right && right_most_descendent->right != current)
        {
          right_most_descendent = right_most_descendent->right;
        }

        if(right_most_descendent->right == current)
        {
          right_most_descendent->right = nullptr;
          ret.push_back(current->val);

          current = current->right;
        }
        else
        {
          right_most_descendent->right = current;
          current = current->left;
        }
      }
    }

    return ret;
  }
};

TEST_CASE("null 1")
{
  TreeNode* r = new TreeNode{0};
  CHECK(Solution().inorderTraversal(r) == std::vector<int>{0});
}

TEST_CASE("null 2")
{
  CHECK(Solution().inorderTraversal(nullptr) == std::vector<int>{});
}

TEST_CASE("example 1")
{
  TreeNode* root = new TreeNode{1};
  root->right = new TreeNode{2};
  root->right->left = new TreeNode{3};
  CHECK(Solution().inorderTraversal(root) == std::vector<int>{1,3,2});
}

TEST_CASE("example 2")
{
  TreeNode* root = new TreeNode{1};
  root->left = new TreeNode{2};
  root->left->left = new TreeNode{3};
  root->left->right = new TreeNode{4};
  root->right = new TreeNode{5};
  root->right->left = new TreeNode{6};
  root->right->right = new TreeNode{7};
  CHECK(Solution().inorderTraversal(root) == std::vector<int>{3, 2, 4, 1, 6, 5, 7});
}
