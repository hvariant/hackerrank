#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        std::nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), std::greater<int>());
        return nums[k-1];
    }
};

TEST_CASE("example 1")
{
  Solution solution;
  std::vector<int> v = { 3,2,1,5,6,4 };
  CHECK(solution.findKthLargest(v, 2) == 5);
}

TEST_CASE("example 2")
{
  Solution solution;
  std::vector<int> v = { 3,2,3,1,2,4,5,5,6 };
  CHECK(solution.findKthLargest(v, 4) == 4);
}
