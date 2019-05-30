#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   int findDuplicate(const std::vector<int>& nums)
   {
      for (size_t i = 0; i < nums.size(); i++)
      {
         for (size_t j = i + 1; j < nums.size(); j++)
         {
            if (nums[i] == nums[j]) return nums[i];
         }
      }

      // this is not possible
      return -1;
   }
};

TEST_CASE("examples")
{
  Solution solution;
  CHECK(solution.findDuplicate({ 3,1,3,4,2 }) == 3);
  CHECK(solution.findDuplicate({ 1,3,4,2,2 }) == 2);
}
