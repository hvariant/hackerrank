// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/646/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   // tortoise and hare
   bool isHappy(int n)
   {
      const auto f = [](int n)
      {
         int r = 0;
         while (n > 0)
         {
            r += (n % 10) * (n % 10);
            n = n / 10;
         }
         return r;
      };

      int tortoise = f(n);
      int hare = f(f(n));
      while (tortoise != hare)
      {
         tortoise = f(tortoise);
         hare = f(f(hare));
      }
      return tortoise == 1;
   }
};

TEST_CASE("example")
{
  Solution solution;
  CHECK(solution.isHappy(19));
}
