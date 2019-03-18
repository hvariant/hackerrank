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
  std::vector<std::vector<int>> zigzagLevelOrder(const TreeNode* root) {
    if(root == nullptr) return {};

    std::vector<std::vector<int>> levels;
    std::queue<std::pair<const TreeNode*, size_t>> Q;
    Q.push({root, 0});

    while(!Q.empty())
    {
      auto top_pair = Q.front();
      Q.pop();

      auto cur = top_pair.first;
      auto level = top_pair.second;
      if(levels.size() < level+1)
      {
        levels.resize(level+1);
      }
      levels[level].push_back(cur->val);

      if(cur->left)
      {
        Q.push({cur->left, level+1});
      }
      if(cur->right)
      {
        Q.push({cur->right, level+1});
      }
    }

    for(size_t i=1;i<levels.size();i+=2)
    {
      std::reverse(levels[i].begin(), levels[i].end());
    }

    return levels;
  }
};

TEST_CASE("null 1")
{
  TreeNode* r = new TreeNode{0};
  CHECK(Solution().zigzagLevelOrder(r) == std::vector<std::vector<int>>{{0}});
}

TEST_CASE("null 2")
{
  CHECK(Solution().zigzagLevelOrder(nullptr) == std::vector<std::vector<int>>{});
}

TEST_CASE("example 1")
{
  TreeNode* root = new TreeNode{3};
  root->left = new TreeNode{9};
  root->right = new TreeNode{20};
  root->right->left = new TreeNode{15};
  root->right->right = new TreeNode{7};
  CHECK(Solution().zigzagLevelOrder(root) == std::vector<std::vector<int>>{{3}, {20, 9}, {15, 7}});
}
