#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <limits>

class Solution
{
public:
    bool increasingTriplet(const std::vector<int>& nums) {
       if (nums.size() < 3) return false;

       int smallest, smallest_after;

       smallest = nums[0];
       smallest_after = std::numeric_limits<int>::max();
       for (size_t i = 1; i < nums.size(); i++)
       {
          if (nums[i] <= smallest)
          {
             smallest = nums[i];
          }
          else if (nums[i] <= smallest_after) // nums[i] > smallest
          {
             smallest_after = nums[i];
          }
          else // nums[i] > smallest_after && nums[i] > smallest && smallest_after > smallest
          {
             return true;
          }
       }

       return false;
    }
};

TEST_CASE("Example 1")
{
   Solution solution;
   CHECK(solution.increasingTriplet({ 1,2,3,4,5 }) == true);
}

TEST_CASE("Example 2")
{
   Solution solution;
   CHECK(solution.increasingTriplet({ 5,4,3,2,1 }) == false);
}

TEST_CASE("Example 3")
{
   Solution solution;
   CHECK(solution.increasingTriplet({ 0,4,2,1,0,-1,-3 }) == false);
}

TEST_CASE("Example 4")
{
   Solution solution;
   CHECK(solution.increasingTriplet({ 2,1,5,0,4,6 }) == true);
}

