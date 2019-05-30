#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
    size_t longestConsecutive(std::vector<int>& nums)
    {
       if (nums.empty()) return 0;

       std::sort(nums.begin(), nums.end());
       // remove duplicates:
       //   https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
       nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );

       size_t r = 1;
       size_t i = 0;
       while (i < nums.size())
       {
          size_t j = i + 1;
          while (j < nums.size() && nums[j] == nums[j - 1] + 1) j++;
          r = std::max(r, j - i);
          i = j;
       }
       return r;
    }
};

TEST_CASE("examples")
{
  Solution solution;
  std::vector<int> v = { 100, 4, 200, 1, 3, 2 };
  CHECK(solution.longestConsecutive(v) == 4);
  v = { 1,2,0,1 };
  CHECK(solution.longestConsecutive(v) == 3);
}
