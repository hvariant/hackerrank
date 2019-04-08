#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   int uniquePaths(int m, int n)
   {
      std::vector<std::vector<size_t>> dp(m, std::vector<size_t>(n, 1));
      for (size_t i = 1; i < m; i++)
      {
         for (size_t j = 1; j < n; j++)
         {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
         }
      }

      return dp[m - 1][n - 1];
   }
};

TEST_CASE("Examples")
{
   Solution solution;
   CHECK(solution.uniquePaths(3, 2) == 3);
   CHECK(solution.uniquePaths(7, 3) == 28);
}
