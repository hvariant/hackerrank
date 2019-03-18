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

// https://www.codeproject.com/Articles/418776/How-to-replace-recursive-functions-using-stack-and
class Solution {
public:
  TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    std::stack<Snapshot> S;

    TreeNode* ret_val = nullptr;
    S.push({Stage::BEGIN, preorder.begin(), preorder.end(), inorder.begin(), inorder.end()});
    while(!S.empty())
    {
      auto snapshot = S.top();
      S.pop();

      if(snapshot.preorder_begin == snapshot.preorder_end)
      {
        ret_val = nullptr;
        continue;
      }
      if(snapshot.preorder_begin + 1 == snapshot.preorder_end)
      {
        ret_val = new TreeNode{*(snapshot.preorder_begin)};
        continue;
      }

      switch(snapshot.stage)
      {
        case Stage::BEGIN:
        {
          snapshot.root = new TreeNode{*(snapshot.preorder_begin)};
          auto it = std::find(snapshot.inorder_begin, snapshot.inorder_end, *(snapshot.preorder_begin));
          auto i = std::distance(snapshot.inorder_begin, it);

          snapshot.stage = Stage::RIGHT;
          S.push(snapshot);
          S.push({Stage::BEGIN,
                  snapshot.preorder_begin + i + 1, snapshot.preorder_end,
                  snapshot.inorder_begin + i + 1,  snapshot.inorder_end
                 });

          snapshot.stage = Stage::LEFT;
          S.push(snapshot);
          S.push({Stage::BEGIN,
                  snapshot.preorder_begin + 1, snapshot.preorder_begin + 1 + i,
                  snapshot.inorder_begin,      snapshot.inorder_begin + i
                 });
          break;
        }
        case Stage::LEFT:
        {
          snapshot.root->left = ret_val;
          break;
        }
        case Stage::RIGHT:
        {
          snapshot.root->right = ret_val;
          ret_val = snapshot.root;
          break;
        }
      }
    }

    return ret_val;
  }

private:
  enum class Stage
  {
    BEGIN,
    LEFT,
    RIGHT
  };

  struct Snapshot
  {
    Stage stage;

    const std::vector<int>::const_iterator preorder_begin;
    const std::vector<int>::const_iterator preorder_end;
    const std::vector<int>::const_iterator inorder_begin;
    const std::vector<int>::const_iterator inorder_end;

    TreeNode* root{nullptr};
  };
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
