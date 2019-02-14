// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/578/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
    std::vector<int> intersect(const std::vector<int>& nums1, const std::vector<int>& nums2) {
      std::vector<int> nums1_sorted = nums1;
      std::vector<int> nums2_sorted = nums2;
      std::sort(nums1_sorted.begin(), nums1_sorted.end());
      std::sort(nums2_sorted.begin(), nums2_sorted.end());

      std::vector<int> nums_result;
      size_t i, j;
      i = j = 0;
      while(i < nums1_sorted.size() && j < nums2_sorted.size())
      {
        if(nums1_sorted[i] == nums2_sorted[j])
        {
          nums_result.push_back(nums1_sorted[i]);
          i++; j++;
        }
        else
        {
          if(nums1_sorted[i] < nums2_sorted[j]) { i++; }
          else { j++; }
        }
      }

      return nums_result;
    }
};

TEST_CASE("example 1")
{
  Solution solution;
  CHECK(solution.intersect({1,2,2,1}, {2,2}) == std::vector<int>{2,2});
}

TEST_CASE("example 2")
{
  Solution solution;
  CHECK(solution.intersect({4,9,5}, {9,4,9,8,4}) == std::vector<int>{4,9});
}
