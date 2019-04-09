// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/646/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   int trailingZeroes(int n) {
      return std::min(twos(n), fives(n));
   }

private:
   int twos(int n)
   {
      if (n < 2)
      {
         return 0;
      }
      return n / 2 + twos(n / 2);
   }

   int fives(int n)
   {
      if (n < 5)
      {
         return 0;
      }
      return n / 5 + fives(n / 5);
   }
};

TEST_CASE("example")
{
  Solution solution;
  CHECK(solution.trailingZeroes(3) == 0);
  CHECK(solution.trailingZeroes(5) == 1);
  CHECK(solution.trailingZeroes(6) == 1);
}
