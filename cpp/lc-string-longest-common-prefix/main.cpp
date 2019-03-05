#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <vector>

class Solution {
public:
    std::string longestCommonPrefix(const std::vector<std::string>& strs) {
       if (strs.empty())
       {
          return "";
       }

       std::string_view prefix = strs[0];
       for (size_t i = 1; i < strs.size() && !prefix.empty(); i++)
       {
          if (strs[i].size() < prefix.size())
          {
             prefix.remove_suffix(prefix.size() - strs[i].size());
          }

          for (size_t j = 0; j < prefix.size(); j++)
          {
             if (prefix[j] != strs[i][j])
             {
                prefix.remove_suffix(prefix.size() - j);
                break;
             }
          }
       }

       return std::string(prefix);
    }
};

TEST_CASE("Example1")
{
  Solution solution;
  CHECK(solution.longestCommonPrefix({ "flower","flow","flight" }) == "fl");
}

TEST_CASE("Example2")
{
  Solution solution;
  CHECK(solution.longestCommonPrefix({ "dog","racecar","car" }) == "");
}
