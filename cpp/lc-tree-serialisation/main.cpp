#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

namespace
{
  struct TreeNode {
    int val;
    TreeNode *left{nullptr};
    TreeNode *right{nullptr};
  };
}

#include <optional>
#include <numeric>

class Codec {
public:
   // Encodes a tree to a single string.
   std::string serialize(TreeNode* root) {
      if (root == nullptr) return "";

      std::vector<std::optional<int>> result;
      do_serialise(root, result);

      std::string r = std::to_string(result[0].value());
      for(size_t i=1;i<result.size();i++)
      {
         r += ",";
         if (result[i].has_value())
         {
            r += std::to_string(result[i].value());
         }
         else
         {
            r += "null";
         }
      }

      return r;
   }

   // Decodes your encoded data to tree.
   TreeNode* deserialize(const std::string_view& data) {
      if (data.empty()) return nullptr;

      std::vector<std::string> nodes_str;
      auto pos = 0;
      auto next_pos = data.find_first_of(',');
      while (next_pos != std::string_view::npos)
      {
         nodes_str.push_back(std::string(data.substr(pos, next_pos - pos)));

         pos = next_pos + 1;
         next_pos = data.find_first_of(',', pos);
      }
      nodes_str.push_back(std::string(data.substr(pos)));

      auto it = nodes_str.cbegin();
      auto p = do_deserialise(it, nodes_str.cend());
      return p.second;
   }

private:
   void do_serialise(TreeNode* root, std::vector<std::optional<int>>& result)
   {
      if (root == nullptr)
      {
         result.push_back(std::nullopt);
         return;
      }

      result.push_back(root->val);
      do_serialise(root->left, result);
      do_serialise(root->right, result);
   }

   std::pair<std::vector<std::string>::const_iterator,TreeNode*> do_deserialise(
      std::vector<std::string>::const_iterator begin,
      std::vector<std::string>::const_iterator end
   )
   {
      if (begin == end)
      {
         return { end, nullptr };
      }

      if (*begin == "null")
      {
         return { begin + 1, nullptr };
      }

      auto val = std::stoi(*begin);
      TreeNode* root = new TreeNode{ val };

      auto it = begin + 1;
      {
         auto p = do_deserialise(it, end);
         it = p.first;
         root->left = p.second;
      }
      {
         auto p = do_deserialise(it, end);
         it = p.first;
         root->right = p.second;
      }

      return { it, root };
   }
};

bool tree_equal(TreeNode* T1, TreeNode* T2)
{
  if(T1 == nullptr || T2 == nullptr)
  {
    return T1 == T2;
  }

  if(T1->val != T2->val)
  {
    return false;
  }

  return tree_equal(T1->left, T2->left) && tree_equal(T1->right, T2->right);
}

TEST_CASE("null 1")
{
   CHECK(Codec().serialize(nullptr) == "");
   CHECK(Codec().deserialize("") == nullptr);
}

TEST_CASE("example 1")
{
   TreeNode* root = new TreeNode{ 1 };
   root->left = new TreeNode{ 2 };
   root->right = new TreeNode{ 3 };
   root->right->left = new TreeNode{ 4 };
   root->right->right = new TreeNode{ 5 };
   std::string expected = "1,2,null,null,3,4,null,null,5,null,null";
   CHECK(Codec().serialize(root) == expected);
   auto reserialised = Codec().deserialize(expected);
   CHECK(tree_equal(reserialised, root));
}
