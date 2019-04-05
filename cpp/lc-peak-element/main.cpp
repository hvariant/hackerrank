#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   int findPeakElement(const std::vector<int>& nums)
   {
      assert(nums.size() > 0);
      if (nums.size() == 1)
      {
         return 0;
      }

      int left = 0, right = nums.size() - 1;
      const auto is_peak = [&nums](int i)
      {
         if (i == 0)
         {
            return nums[i] > nums[i + 1];
         }
         if (i == nums.size() - 1)
         {
            return nums[i - 1] < nums[i];
         }
         return nums[i - 1] < nums[i] && nums[i] > nums[i + 1];
      };

      // invariant: nums[left] > nums[left-1] && nums[right] > nums[right+1]
      while (left < right)
      {
         size_t mid = (right - left) / 2 + left;
         if (is_peak(mid))
         {
            return mid;
         }

         // edge case with left + 1 == right
         if (mid == left)
         {
            left = left + 1;
         }
         else // mid > left
         {
            // there must be a peak on the left side
            if (nums[mid] < nums[mid - 1])
            {
               right = mid - 1;
            }
            // otherwise, there is a probably peak on the right side
            // a special case is this: 1 2 9 9 9
            // you could consider any of the 9's a 'half-peak', but it's not entirely clear
            // in the problem description that this should be accepted
            else
            {
               while (mid < right && nums[mid] >= nums[mid + 1]) mid++;
               left = mid;
            }
         }
      }

      return left;
   }
};

TEST_CASE("Example1")
{
  Solution solution;
  CHECK(solution.findPeakElement({ 1,2,3,1 }) == 2);
}

TEST_CASE("Example2")
{
  Solution solution;
  auto v = solution.findPeakElement({ 1,2,1,3,5,6,4 });
  bool correct = (v == 1 || v == 5);
  CHECK(correct);
}

TEST_CASE("Example3")
{
  Solution solution;
  auto v = solution.findPeakElement({ 1,2,9,9,9 });
  CHECK(v == 4);
}
