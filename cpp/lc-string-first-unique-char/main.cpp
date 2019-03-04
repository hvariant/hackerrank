#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <vector>

class Solution {
public:
   // std::string_view is faster than std::string
   int firstUniqChar(const std::string_view& s) {
      std::vector<size_t> m(26, 0);
      for (char c : s)
      {
         // assume all letters are lowercase
         m[c - 'a']++;
      }

      for (int i = 0; i < s.size(); i++)
      {
         if (m[s[i] - 'a'] == 1) return i;
      }
      return -1;
   }
};

TEST_CASE("Example1")
{
  Solution solution;
  CHECK(solution.firstUniqChar("leetcode") == 0);
}

TEST_CASE("Example2")
{
  Solution solution;
  CHECK(solution.firstUniqChar("loveleetcode") == 2);
}

TEST_CASE("Example3")
{
  Solution solution;
  CHECK(solution.firstUniqChar("owow") == -1);
}
