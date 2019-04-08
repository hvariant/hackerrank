// https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/553/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   int coinChange(const std::vector<int>& coins, size_t amount) {
      std::vector<size_t> dp(amount + 1, std::numeric_limits<size_t>::max());

      dp[0] = 0;
      for (size_t x = 1; x <= amount; x++)
      {
         for (auto coin : coins)
         {
            for (size_t i = 1; coin*i <= x; i++)
            {
               if (dp[x - coin * i] != std::numeric_limits<size_t>::max())
               {
                  dp[x] = std::min(dp[x], dp[x - coin * i] + i);
               }
            }
         }
      }

      return dp[amount] == std::numeric_limits<size_t>::max() ? -1 : static_cast<int>(dp[amount]);
   }
};

TEST_CASE("examples")
{
   Solution solution;
   CHECK(solution.coinChange({ 1,2,5 }, 11) == 3);
   CHECK(solution.coinChange({ 2 }, 3) == -1);
}
