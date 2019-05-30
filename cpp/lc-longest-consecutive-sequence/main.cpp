#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <unordered_set>

class Solution {
public:
   //size_t longestConsecutive(std::vector<int>& nums)
   //{
   //   if (nums.empty()) return 0;

   //   std::sort(nums.begin(), nums.end());
   //   // remove duplicates:
   //   //   https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
   //   nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );

   //   size_t r = 1;
   //   size_t i = 0;
   //   while (i < nums.size())
   //   {
   //      size_t j = i + 1;
   //      while (j < nums.size() && nums[j] == nums[j - 1] + 1) j++;
   //      r = std::max(r, j - i);
   //      i = j;
   //   }
   //   return r;
   //}

   int longestConsecutive(const std::vector<int>& nums)
   {
      if (nums.empty()) return 0;

      std::unordered_set<int> S(nums.begin(), nums.end());
      int r = 1;
      for (auto n : nums)
      {
         if (S.count(n) == 0)
         {
            continue;
         }

         S.erase(n);

         int lower = n - 1;
         while (S.count(lower) > 0)
         {
            S.erase(lower);
            lower--;
         }
         lower++;

         int upper = n + 1;
         while (S.count(upper) > 0)
         {
            S.erase(upper);
            upper++;
         }
         upper--;

         r = std::max(r, upper - lower + 1);
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
