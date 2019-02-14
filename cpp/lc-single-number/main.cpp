// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/578/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
  int singleNumber(const std::vector<int>& nums) {
    return std::accumulate(nums.begin(), nums.end(), 0, [](int a, int b) { return a ^ b; });
  }
};

TEST_CASE("example 1")
{
  Solution solution;
  CHECK(solution.singleNumber({2,2,1}) == 1);
}

TEST_CASE("example 2")
{
  Solution solution;
  CHECK(solution.singleNumber({4,1,2,1,2}) == 4);
}
