// https://leetcode.com/explore/interview/card/top-interview-questions-easy/94/trees/631/

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
  TreeNode* sortedArrayToBST(const std::vector<int>& nums) {
    if(nums.empty()) return nullptr;

    return sortedArrayToBSTRanged(nums, 0, nums.size()-1);
  }

private:
  TreeNode* sortedArrayToBSTRanged(const std::vector<int>& nums, size_t L, size_t U) {
    if(L > U)
    {
      return nullptr;
    }
    else if(L == U)
    {
      return new TreeNode{nums[L]};
    }

    const auto M = (L+U)/2;
    TreeNode* n = new TreeNode{nums[M]};
    if(L < M)
      n->left = sortedArrayToBSTRanged(nums, L, M-1);
    if(M < U)
      n->right = sortedArrayToBSTRanged(nums, M+1, U);

    return n;
  }
};

TEST_CASE("null")
{
  Solution solution;
  CHECK(solution.sortedArrayToBST({}) == nullptr);
}

TEST_CASE("example 1")
{
  Solution solution;
  auto n = solution.sortedArrayToBST({1});
  REQUIRE_FALSE(n == nullptr);
  CHECK(n->val == 1);
  CHECK(n->left == nullptr);
  CHECK(n->right == nullptr);
}

TEST_CASE("example 2")
{
  Solution solution;
  auto n = solution.sortedArrayToBST({-10,-3,0,5,9});
  REQUIRE(n);
  CHECK(n->val == 0);
  REQUIRE(n->left);
  CHECK(n->left->val == -10);
  REQUIRE(n->left->right);
  CHECK(n->left->right->val == -3);
  REQUIRE(n->right);
  CHECK(n->right->val == 5);
  REQUIRE(n->right->right);
  CHECK(n->right->right->val == 9);
}
