#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <queue>

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
  TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    return _buildTree(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
  }

private:
  TreeNode* _buildTree(
    const std::vector<int>::const_iterator preorder_begin,
    const std::vector<int>::const_iterator preorder_end,
    const std::vector<int>::const_iterator inorder_begin,
    const std::vector<int>::const_iterator inorder_end)
  {
    if(preorder_begin == preorder_end)
    {
      return nullptr;
    }
    if(preorder_begin + 1 == preorder_end)
    {
      return new TreeNode{*preorder_begin};
    }

    TreeNode* root = new TreeNode{*preorder_begin};
    auto it = std::find(inorder_begin, inorder_end, *preorder_begin);
    auto i = std::distance(inorder_begin, it);

    root->left = buildTree(
          std::vector<int>{preorder_begin + 1, preorder_begin + 1 + i},
          std::vector<int>{inorder_begin, inorder_begin + i}
          );
    root->right = buildTree(
          std::vector<int>{preorder_begin + i + 1, preorder_end},
          std::vector<int>{inorder_begin + i + 1, inorder_end}
          );

    return root;
  }
};

bool compare_tree(TreeNode* cur1, TreeNode* cur2)
{
  if(cur1 == nullptr || cur2 == nullptr)
  {
    return cur1 == cur2;
  }

  if(cur1->val != cur2->val) return false;
  return compare_tree(cur1->left, cur2->left) && compare_tree(cur1->right, cur2->right);
}

TEST_CASE("null")
{
  Solution solution;
  CHECK(solution.buildTree({}, {}) == nullptr);
}

TEST_CASE("example 1")
{
  Solution solution;

  auto output = solution.buildTree({3,9,20,15,7}, {9,3,15,20,7});

  TreeNode* root = new TreeNode{3};
  root->left = new TreeNode{9};
  root->right = new TreeNode{20};
  root->right->left = new TreeNode{15};
  root->right->right = new TreeNode{7};

  CHECK(compare_tree(output, root));
}

TEST_CASE("ASan")
{
  Solution solution;
  auto output = solution.buildTree({1,2,3,4}, {4,3,2,1});
  TreeNode* root = new TreeNode{1};
  root->left = new TreeNode{2};
  root->left->left = new TreeNode{3};
  root->left->left->left = new TreeNode{4};

  CHECK(compare_tree(root, output));
}
