#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   int firstMissingPositive(std::vector<int>& nums)
   {
      for (size_t i = 0; i < nums.size(); i++)
      {
         while (
            // the number is in valid range
            nums[i] >= 1 && nums[i] <= nums.size()
            // the number is not already in the correct place
            && nums[i] != i + 1
            // swapping actually changes something
            && nums[i] != nums[nums[i] - 1])
         {
            std::swap(nums[i], nums[nums[i] - 1]);
         }
      }

      for (size_t i = 0; i < nums.size(); i++)
      {
         if (nums[i] != i + 1)
         {
            return i + 1;
         }
      }
      return nums.size() + 1;
   }
};

TEST_CASE("Example1")
{
  Solution solution;
  {
     std::vector<int> v{ 1,2,0 };
     CHECK(solution.firstMissingPositive(v) == 3);
  }
  {
     std::vector<int> v{ 3,4,-1,1 };
     CHECK(solution.firstMissingPositive(v) == 2);
  }
  {
     std::vector<int> v{ 7,8,9,11,12 };
     CHECK(solution.firstMissingPositive(v) == 1);
  }
  {
     std::vector<int> v{ 1,2,3 };
     CHECK(solution.firstMissingPositive(v) == 4);
  }
}
