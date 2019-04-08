#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   // C(m+n-2, n-1) = C(m+n-2,m-1)
   int uniquePaths(int m, int n)
   {
      int N = m + n - 2;
      int R = std::min(m - 1, n - 1);

      uint64_t num = 1;
      uint64_t denom = 1;

      for (size_t i = 0; i < R; i++)
      {
         num *= (N - i);
      }
      for (size_t i = 0; i < R; i++)
      {
         denom *= (R - i);
      }

      return static_cast<int>(num / denom);
   }
};

TEST_CASE("Examples")
{
   Solution solution;
   CHECK(solution.uniquePaths(3, 2) == 3);
   CHECK(solution.uniquePaths(7, 3) == 28);
}
