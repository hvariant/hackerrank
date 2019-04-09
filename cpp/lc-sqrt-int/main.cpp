#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   int mySqrt(int x) {
      if (x <= 1) return x;

      int left = 1, right = x;

      // invariant: left * left <= x, right * right > x
      while (left < right)
      {
         int mid = (right - left) / 2 + left;

         if (left == mid)
         {
            break;
         }

         if (mid == x / mid)
         {
            return mid;
         }
         else if (mid < x / mid)
         {
            left = mid;
         }
         else
         {
            right = mid;
         }
      }

      return left;
   }
};

TEST_CASE("example")
{
  Solution solution;
  CHECK(solution.mySqrt(0) == 0);
  CHECK(solution.mySqrt(1) == 1);
  CHECK(solution.mySqrt(2) == 1);
  CHECK(solution.mySqrt(10) == 3);
  CHECK(solution.mySqrt(100) == 10);
}
