// https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/553/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   int coinChange(const std::vector<int>& coins, size_t amount) {
      std::vector<int> dp(amount + 1, std::numeric_limits<int>::max());

      dp[0] = 0;
      for (int x = 1; x <= amount; x++)
      {
         for (auto coin : coins)
         {
            if (x >= coin && dp[x - coin] != std::numeric_limits<int>::max())
            {
               dp[x] = std::min(dp[x], dp[x - coin] + 1);
            }
         }
      }

      return dp[amount] == std::numeric_limits<int>::max() ? -1 : dp[amount];
   }
};

TEST_CASE("examples")
{
   Solution solution;
   CHECK(solution.coinChange({ 1,2,5 }, 11) == 3);
   CHECK(solution.coinChange({ 2 }, 3) == -1);
}
