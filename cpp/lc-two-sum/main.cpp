// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/578/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <algorithm>

class Solution {
public:
  std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::vector<std::pair<int, int>> nums_with_index;
    for(size_t i=0;i<nums.size();i++)
    {
      nums_with_index.push_back({nums[i],static_cast<int>(i)});
    }
    std::sort(nums_with_index.begin(), nums_with_index.end());

    size_t i=0;
    size_t j=1;
    while(i < nums_with_index.size()-1)
    {
      int sum = nums_with_index[i].first + nums_with_index[j].first;
      if(sum == target)
      {
        return {nums_with_index[i].second, nums_with_index[j].second};
      }
      else if(sum > target)
      {
        i++;
        j = i+1;
      }
      else
      {
        j++;
        if(j >= nums_with_index.size())
        {
          i++;
          j = i+1;
        }
      }
    }

    return {}; // this is impossible per problem description
  }
};

TEST_CASE("example 1")
{
  CHECK(Solution().twoSum({2,7,11,15}, 9) == std::vector<int>{0,1});
}

TEST_CASE("example 2")
{
  CHECK(Solution().twoSum({3,2,4}, 6) == std::vector<int>{1,2});
}
