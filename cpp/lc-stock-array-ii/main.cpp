// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/564/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <optional>

class Solution {
public:
  int maxProfit(const std::vector<int>& prices) {
    using std::vector;

    if(prices.size() == 0) return 0;

    int total_profit = 0;
    for(size_t i=0;i<prices.size()-1;i++)
    {
      if(prices[i] < prices[i+1])
      {
        total_profit += prices[i+1] - prices[i];
      }
    }
    return total_profit;
  }
};

TEST_CASE("Example1")
{
  Solution solution;
  CHECK(solution.maxProfit({7,1,5,3,6,4}) == 7);
}


TEST_CASE("Example2")
{
  Solution solution;
  CHECK(solution.maxProfit({1,2,3,4,5}) == 4);
}

TEST_CASE("Example3")
{
  Solution solution;
  CHECK(solution.maxProfit({7,6,4,3,1}) == 0);
}

TEST_CASE("Example4")
{
  Solution solution;
  CHECK(solution.maxProfit({1}) == 0);
}

TEST_CASE("Example5")
{
  Solution solution;
  CHECK(solution.maxProfit({1,2}) == 1);
}

TEST_CASE("Example6")
{
  Solution solution;
  CHECK(solution.maxProfit({}) == 0);
}

TEST_CASE("WA1")
{
  Solution solution;
  CHECK(solution.maxProfit({6,1,3,2,4,7}) == 7);
}

TEST_CASE("MLE")
{
  Solution solution;
  std::vector<int> large_array;
  for(int i=40000;i>=0;i--)
  {
    large_array.push_back(i);
  }

  CHECK(solution.maxProfit(large_array) == 0);
}
