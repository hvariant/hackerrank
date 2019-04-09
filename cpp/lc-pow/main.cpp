// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/646/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   double myPow(double x, int n_signed) {
      long long n = std::abs(static_cast<long long>(n_signed));
      double r = 1.0;
      double f = x;
      while (n > 0)
      {
         if (n % 2 != 0)
         {
            r *= f;
         }

         n = n / 2;
         f = f * f;
      }

      if (n_signed < 0)
      {
         return 1.0 / r;
      }
      return r;
   }
};

TEST_CASE("example")
{
  Solution solution;
  CHECK(solution.myPow(1.0, 12) == 1.0);
  CHECK(solution.myPow(10.0, 12) == 1e12);
  CHECK(solution.myPow(2.0, -2) == 0.25);
}
