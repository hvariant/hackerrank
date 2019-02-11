// https://leetcode.com/explore/interview/card/top-interview-questions-easy/96/sorting-and-searching/587/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <algorithm>

class Solution {
public:
  void merge(std::vector<int>& nums1, int m, const std::vector<int>& nums2, int n) {
    // STL solution
//    std::copy_n(nums2.begin(), n, nums1.begin() + m);
//    std::inplace_merge(nums1.begin(), nums1.begin() + m, nums1.begin() + m + n);

    // merge from back
    auto idx = m + n - 1;
    auto idx1 = m - 1;
    auto idx2 = n - 1;
    while(idx1 >= 0 && idx2 >= 0)
    {
      if(nums1[idx1] > nums2[idx2])
      {
        nums1[idx--] = nums1[idx1--];
      }
      else
      {
        nums1[idx--] = nums2[idx2--];
      }
    }

    while(idx1 >= 0)
    {
      nums1[idx--] = nums1[idx1--];
    }
    while(idx2 >= 0)
    {
      nums1[idx--] = nums2[idx2--];
    }
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
