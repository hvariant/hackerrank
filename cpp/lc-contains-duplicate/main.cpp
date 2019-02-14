// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/578/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_set>
#include <vector>

class Solution {
public:
  bool containsDuplicate(const std::vector<int>& nums) {
    if(nums.empty()) return false;

    std::unordered_set<int> S;
    S.insert(nums[0]);
    for(size_t i=1;i<nums.size();i++)
    {
      if(S.count(nums[i]) > 0)
      {
        return true;
      }
      S.insert(nums[i]);
    }
    return false;
  }
};

TEST_CASE("example null")
{
  Solution solution;
  CHECK(solution.containsDuplicate({}) == false);
}

TEST_CASE("example 1")
{
  Solution solution;
  CHECK(solution.containsDuplicate({1,2,3,1}) == true);
}

TEST_CASE("example 2")
{
  Solution solution;
  CHECK(solution.containsDuplicate({1,2,3,4}) == false);
}

TEST_CASE("example 3")
{
  Solution solution;
  CHECK(solution.containsDuplicate({1,1,1,3,3,4,3,2,4,2}) == true);
}
