// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/646/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string_view>

class Solution {
public:
   int titleToNumber(std::string_view s)
   {
      int r = 0;
      for (size_t i = 0; i < s.size(); i++)
      {
         int digit = s[i] - 'A' + 1;
         r = 26 * r + digit;
      }
      return r;
   }
};

TEST_CASE("example")
{
  Solution solution;
  CHECK(solution.titleToNumber("A") == 1);
  CHECK(solution.titleToNumber("AB") == 28);
  CHECK(solution.titleToNumber("ZY") == 701);
}
