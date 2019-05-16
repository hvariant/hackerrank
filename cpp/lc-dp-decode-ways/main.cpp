#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string_view>

class Solution {
public:
   int numDecodings(std::string_view s) {
      std::vector<int> dp(3, 0);

      if (s[0] > '0')
      {
         dp[0] = 1;
      }
      dp[2] = 1; // i.e. dp[-1]
      for (size_t i = 1; i < s.length(); i++)
      {
         // the digit can mean a 'A' to 'I' (1 to 9)
         if (s[i] > '0')
         {
            dp[(i % 3)] = dp[(i - 1) % 3];
         }
         else
         {
            dp[(i % 3)] = 0;
         }

         // see if s[i-1] + s[i] can be a letter
         std::string double_digit = std::string(s.substr(i - 1, 2));
         int n = std::stoi(double_digit);
         if (n >= 10 && n <= 26)
         {
            // i-2 can be -1, -1 mod 3 = 2, dp[-1] = dp[2] = 1
            dp[i % 3] += dp[(i - 2 + 3) % 3];
         }
      }

      return dp[(s.length() - 1) % 3];
   }
};

TEST_CASE("Examples")
{
   CHECK(Solution().numDecodings("12") == 2);
   CHECK(Solution().numDecodings("226") == 3);
   CHECK(Solution().numDecodings("2222") == 5);
   CHECK(Solution().numDecodings("101010101010101010101010") == 1);
   CHECK(Solution().numDecodings("0") == 0);
   CHECK(Solution().numDecodings("19") == 2);
}
