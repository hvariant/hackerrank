#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

namespace
{
  struct TreeNode {
    int val;
    TreeNode *left{nullptr};
    TreeNode *right{nullptr};
    TreeNode *next{nullptr};

    TreeNode(int x) : val(x) {}
  };
}

#include <queue>

class Solution {
public:
    std::vector<int> rightSideView(TreeNode* root)
    {
       std::queue<std::pair<TreeNode*, size_t>> Q;
       std::vector<int> R;

       if (root)
       {
          Q.push({ root, 0 });
       }

       while (!Q.empty())
       {
          auto cur = Q.front();
          Q.pop();

          auto cur_node = cur.first;
          auto cur_step = cur.second;

          if (R.size() < cur_step + 1)
          {
             R.push_back(cur_node->val);
          }
          else
          {
             R[cur_step] = cur_node->val;
          }

          if (cur_node->left)
          {
             Q.push({ cur_node->left, cur_step + 1 });
          }
          if (cur_node->right)
          {
             Q.push({ cur_node->right, cur_step + 1 });
          }
       }

       return R;
    }
};

TEST_CASE("null 1")
{
   CHECK(Solution().rightSideView(nullptr) == std::vector<int>{});
}

TEST_CASE("example 1")
{
  auto input = new TreeNode{1};
  input->left = new TreeNode{2};
  input->left->right = new TreeNode{5};
  input->right = new TreeNode{3};
  input->right->right = new TreeNode{4};

  CHECK(Solution().rightSideView(input) == std::vector<int>{1,3,4});
}
