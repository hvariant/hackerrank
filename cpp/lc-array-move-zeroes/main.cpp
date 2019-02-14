// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/578/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <algorithm>

class Solution {
public:
  void moveZeroes(std::vector<int>& nums) {
    size_t number_of_zeros = static_cast<size_t>(std::count(nums.begin(), nums.end(), 0));
    nums.erase(std::remove(nums.begin(), nums.end(), 0), nums.end());
    for(size_t i=0;i<number_of_zeros;i++)
    {
      nums.push_back(0);
    }
  }
};

TEST_CASE("example")
{
  std::vector<int> input = {0,1,0,3,12};
  Solution().moveZeroes(input);
  CHECK(input == std::vector<int>{1,3,12,0,0});
}
