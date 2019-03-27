// https://leetcode.com/explore/interview/card/top-interview-questions-easy/94/trees/631/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   void sortColors(std::vector<int>& nums) {
      if (nums.size() <= 1) return;

      int p0 = 0, p2 = static_cast<int>(nums.size() - 1);
      while (p0 < nums.size() && nums[p0] == 0) p0++;
      if (p0 == nums.size()) return;
      while (p2 >= 0 && nums[p2] == 2) p2--;

      const auto shrink_range = [&p0, &p2, &nums]() {
         while (nums[p0] == 0 && p0 < nums.size()) p0++;
         while (nums[p2] == 2 && p2 >= 0) p2--;
      };

      // loop invariant:
      // - for all i < p0, nums[i] == 0
      // - for all i > p2, nums[i] == 2
      // - p0 < p2 && p0 <= i <= p2
      int i = p0;
      while (i <= p2 && p0 < p2)
      {
         if (nums[i] == 0)
         {
            std::swap(nums[i], nums[p0]);
            p0++;

            shrink_range();
            i = std::max(i, p0);
         }
         else if (nums[i] == 2)
         {
            std::swap(nums[i], nums[p2]);
            p2--;

            shrink_range();
            i = std::max(i, p0);
         }
         else
         {
            i++;
         }
      }
   }
};

TEST_CASE("null")
{
  Solution solution;
  auto v = std::vector<int>{};
  solution.sortColors(v);

  CHECK(v.empty());
}

TEST_CASE("example 1")
{
  Solution solution;
  auto v = std::vector<int>{ 2,0,2,1,1,0 };
  solution.sortColors(v);

  CHECK(v == std::vector<int>{0, 0, 1, 1, 2, 2});
}

TEST_CASE("example 2")
{
  Solution solution;
  auto v = std::vector<int>{ 1, 0 };
  solution.sortColors(v);

  CHECK(v == std::vector<int>{0, 1});
}

TEST_CASE("example 3")
{
  Solution solution;
  auto v = std::vector<int>{ 1, 2, 0 };
  solution.sortColors(v);

  CHECK(v == std::vector<int>{0, 1, 2});
}

TEST_CASE("null 2")
{
   Solution solution;
   auto v = std::vector<int>{ 1,1,1 };
   solution.sortColors(v);

   CHECK(v == std::vector<int>{1, 1, 1});
}

TEST_CASE("example 4")
{
   Solution solution;
   auto v = std::vector<int>{ 2,1,2 };
   solution.sortColors(v);

   CHECK(v == std::vector<int>{1, 2, 2});
}
