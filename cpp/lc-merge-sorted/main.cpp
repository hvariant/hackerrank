// https://leetcode.com/explore/interview/card/top-interview-questions-easy/96/sorting-and-searching/587/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <algorithm>

class Solution {
public:
  void merge(std::vector<int>& nums1, int m, const std::vector<int>& nums2, int n) {
    std::copy_n(nums2.begin(), n, nums1.begin() + m);
    std::inplace_merge(nums1.begin(), nums1.begin() + m, nums1.begin() + m + n);
  }
};

TEST_CASE("example")
{
  Solution solution;
  std::vector<int> nums1 = {1,2,3,0,0,0};
  std::vector<int> nums2 = {2,5,6};

  solution.merge(nums1, 3, nums2, 3);
  CHECK(nums1 == std::vector<int>{1,2,2,3,5,6});
}
