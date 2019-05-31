#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   int findDuplicate(const std::vector<int>& nums)
   {
      int tortoise = nums[0];
      int hare = nums[0];
      do
      {
         tortoise = nums[tortoise];
         hare = nums[nums[hare]];
      } while (tortoise != hare);

      hare = tortoise;
      tortoise = nums[0];
      while(hare != tortoise)
      {
         tortoise = nums[tortoise];
         hare = nums[hare];
      }

      return tortoise;
   }
};

TEST_CASE("examples")
{
  Solution solution;
  CHECK(solution.findDuplicate({ 3,1,3,4,2 }) == 3);
  CHECK(solution.findDuplicate({ 1,3,4,2,2 }) == 2);
}
