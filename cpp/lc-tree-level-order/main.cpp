// https://leetcode.com/explore/interview/card/top-interview-questions-easy/94/trees/628/

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
  std::vector<std::vector<int>> levelOrder(const TreeNode* root)
  {
    std::vector<std::vector<int>> result;

    if(root == nullptr)
    {
      return result;
    }

    std::queue<TraversalNode> Q;
    Q.push(TraversalNode{0,root});
    while(!Q.empty())
    {
      TraversalNode cur = Q.front();
      Q.pop();

      if(result.size() < cur.level+1)
      {
        result.resize(cur.level+1);
      }
      result[cur.level].push_back(cur.node->val);

      if(cur.node->left)
      {
        Q.push(TraversalNode{cur.level+1, cur.node->left});
      }
      if(cur.node->right)
      {
        Q.push(TraversalNode{cur.level+1, cur.node->right});
      }
    }

    return result;
  }

private:
  struct TraversalNode {
    size_t level;
    const TreeNode* node;
  };
};

TEST_CASE("null")
{
  Solution solution;
  CHECK(solution.levelOrder(nullptr) == std::vector<std::vector<int>>{});
}

TEST_CASE("example")
{
  Solution solution;
  TreeNode* tree = new TreeNode(3);
  tree->left = new TreeNode(9);
  tree->right = new TreeNode(20);
  tree->right->left = new TreeNode(15);
  tree->right->right = new TreeNode(7);

  CHECK(solution.levelOrder(tree) == std::vector<std::vector<int>>{});
}
