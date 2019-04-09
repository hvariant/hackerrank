// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/646/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   // (x - 2^k*y) // y + 2^k = x // y
   int divide(int dividend, int divisor) {
      long long x = std::abs(static_cast<long long>(dividend));
      long long y = std::abs(static_cast<long long>(divisor));

      long long r = do_divide(x, y);
      if ((dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0))
      {
         if (r > static_cast<long long>(std::numeric_limits<int>::max()))
         {
            return std::numeric_limits<int>::max();
         }
         else
         {
            return static_cast<int>(r);
         }
      }

      if (r > std::abs(static_cast<long long>(std::numeric_limits<int>::min())))
      {
         return std::numeric_limits<int>::max();
      }
      else if (r == std::abs(static_cast<long long>(std::numeric_limits<int>::min())))
      {
         return std::numeric_limits<int>::min();
      }
      else
      {
         return -static_cast<int>(r);
      }
   }

private:
   long long do_divide(long long x, long long y)
   {
      if (x < y)
      {
         return 0;
      }

      long long f = y;
      long long k = 1;
      while (x >= f)
      {
         f <<= 1;
         k <<= 1;
      }

      if (x == f)
      {
         return k;
      }

      f >>= 1;
      k >>= 1;
      return k + do_divide(x - f, y);
   }
};

TEST_CASE("example")
{
   Solution solution;
   CHECK(solution.divide(10, 3) == 3);
   CHECK(solution.divide(7, -3) == -2);
   CHECK(solution.divide(0, 3) == 0);
   CHECK(solution.divide(std::numeric_limits<int>::min(), 1) == std::numeric_limits<int>::min());
   CHECK(solution.divide(std::numeric_limits<int>::min(), -1) == std::numeric_limits<int>::max());
}
