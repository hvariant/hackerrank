#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   int findLargestElement(const std::vector<int>& nums)
   {
      int left = 0, right = nums.size() - 1;
      while (left < right)
      {
         int mid = (right - left) / 2 + left;

         // special case when left + 1 == right
         if (left == mid)
         {
            return nums[left] > nums[right] ? left : right;
         }
         // e.g. 7 8 9 0 1
         if (nums[mid] > nums[left])
         {
            left = mid;
         }
         // e.g. 7 8 9 0 1 2 3
         else
         {
            right = mid;
         }
      }

      return left;
   }

   int search(const std::vector<int>& nums, int target) {
      if (nums.empty()) return -1;

      int peak = findLargestElement(nums);
      int first_element = (peak + 1) % nums.size();
      int left = 0, right = nums.size()-1;

      while (left < right)
      {
         int mid = (right - left) / 2 + left;

         int mid_mod = (mid + first_element) % nums.size();
         int left_mod = (left + first_element) % nums.size();
         int right_mod = (right + first_element) % nums.size();

         if (nums[mid_mod] == target)
         {
            return mid_mod;
         }
         else if (nums[mid_mod] > target)
         {
            right = mid - 1;
         }
         else
         {
            left = mid + 1;
         }
      }

      {
         int left_mod = (left + first_element) % nums.size();
         int right_mod = (right + first_element) % nums.size();
         if (left >= 0 && nums[left_mod] == target)
         {
            return left_mod;
         }
         if (right < nums.size() && nums[right_mod] == target)
         {
            return right_mod;
         }
      }

      return -1;
   }
};

TEST_CASE("FindPeak1")
{
   Solution solution;
   CHECK(solution.findLargestElement(std::vector<int>{ 1,2,3,4,5,6,7,8,9 }) == 8);
   CHECK(solution.findLargestElement(std::vector<int>{ 9,1,2,3,4,5,6,7,8 }) == 0);
   CHECK(solution.findLargestElement(std::vector<int>{ 8,9,1,2,3,4,5,6,7 }) == 1);
   CHECK(solution.findLargestElement(std::vector<int>{ 2,3,4,5,6,7,8,9,1 }) == 7);
}

TEST_CASE("Example1")
{
  Solution solution;
  auto input = std::vector<int>{ 4,5,6,7,0,1,2 };
  CHECK(solution.search(input, 0) == 4);
}

TEST_CASE("Example2")
{
  Solution solution;
  CHECK(solution.search({ 4,5,6,7,0,1,2 }, 7) == 3);
}

TEST_CASE("Example3")
{
  Solution solution;
  CHECK(solution.search({ 4,5,6,7,0,1,2 }, 5) == 1);
}

TEST_CASE("Null1")
{
  Solution solution;
  CHECK(solution.search({ 4,5,6,7,0,1,2 }, 3) == -1);
}

TEST_CASE("WA1")
{
  Solution solution;
  auto input = std::vector<int>{ 6,7,1,2,3,4,5 };
  CHECK(solution.search(input, 6) == 0);
}

TEST_CASE("WA2")
{
   Solution solution;
   auto input = std::vector<int>{ 9,1,2,3,4,5,6,7,8 };
   CHECK(solution.search(input, 9) == 0);
}
