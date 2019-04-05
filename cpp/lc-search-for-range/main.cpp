#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <optional>

class Solution {
public:
   std::vector<int> searchRange(const std::vector<int>& nums, int target)
   {
      if (nums.size() == 0)
      {
         return { -1,-1 };
      }

      auto first = findFirst(nums, target);
      if (!first.has_value())
      {
         return { -1,-1 };
      }
      auto last = findLast(nums, target);
      return { *first, *last };
   }

private:
   std::optional<int> findFirst(const std::vector<int>& nums, int target)
   {
      int left = 0, right = static_cast<int>(nums.size() - 1);

      // invariant:
      //    exist left <= i <= right such that nums[i] == target
      //    nums[left] <= target
      while (left < right)
      {
         int mid = (right - left) / 2 + left;

         if (nums[mid] == target)
         {
            if (mid == left)
            {
               return left;
            }

            right = mid;
         }
         else if (nums[mid] > target)
         {
            right = mid - 1;
         }
         else
         {
            left = mid + 1;
         }
      }

      return nums[left] == target ? std::optional<int>(left) : std::nullopt;
   }

   std::optional<int> findLast(const std::vector<int>& nums, int target)
   {
      int left = 0, right = static_cast<int>(nums.size() - 1);

      // invariant:
      //    exist left <= i <= right such that nums[i] == target
      //    nums[right] >= target
      while (left < right)
      {
         int mid = (right - left + 1) / 2 + left;

         if (nums[mid] == target)
         {
            if (mid == right)
            {
               return right;
            }

            left = mid;
         }
         else if (nums[mid] > target)
         {
            right = mid - 1;
         }
         else
         {
            left = mid + 1;
         }
      }

      return nums[right] == target ? std::optional<int>(right) : std::nullopt;
   }
};

TEST_CASE("Example1")
{
   Solution solution;
   CHECK(solution.searchRange({ 5,7,7,8,8,10 }, 8) == std::vector<int>{3, 4});
   CHECK(solution.searchRange({ 5,7,7,8,8,10 }, 6) == std::vector<int>{-1, -1});
}

TEST_CASE("RTE 1")
{
   Solution solution;
   CHECK(solution.searchRange({ 2,2 }, 1) == std::vector<int>{-1, -1});
   CHECK(solution.searchRange({ 2,2 }, 2) == std::vector<int>{0, 1});
}

TEST_CASE("null0")
{
   Solution solution;
   CHECK(solution.searchRange({}, 6) == std::vector<int>{-1, -1});
}

TEST_CASE("null1")
{
   Solution solution;
   CHECK(solution.searchRange({ 6 }, 6) == std::vector<int>{0, 0});
   CHECK(solution.searchRange({ 6 }, 7) == std::vector<int>{-1, -1});
}
