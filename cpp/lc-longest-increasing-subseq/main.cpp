#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   size_t lengthOfLIS(const std::vector<int>& nums)
   {
      if (nums.empty()) return 0;

      std::vector<size_t> dp(nums.size(), 1);

      size_t r = 1;
      for (size_t i = 1; i < nums.size(); i++)
      {
         for (size_t j = 0; j < i; j++)
         {
            if (nums[j] < nums[i])
            {
               dp[i] = std::max(dp[j] + 1, dp[i]);
            }
         }

         r = std::max(dp[i], r);
      }

      return r;
   }
};

TEST_CASE("Example null")
{
   Solution solution;
   CHECK(solution.lengthOfLIS({}) == 0);
}

TEST_CASE("Example1")
{
   Solution solution;
   CHECK(solution.lengthOfLIS({ 10,9,2,5,3,7,101,18 }) == 4);
}
