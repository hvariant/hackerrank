#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <algorithm>
#include <vector>
#include <unordered_map>

class Solution {
public:
   // naive approach, barely passes
   std::vector<std::vector<int>> threeSum(const std::vector<int>& nums) {
      std::unordered_map<int, size_t> int_count;
      for (auto n : nums)
      {
         if (int_count.count(n) == 0)
         {
            int_count.emplace(n, 1);
         }
         else
         {
            int_count[n]++;
         }
      }

      std::set<std::vector<int>> ret;
      for (size_t i = 0; i < nums.size(); i++)
      {
         for (size_t j = i + 1; j < nums.size(); j++)
         {
            int complement = -(nums[i] + nums[j]);
            size_t min_count = 1;
            if (complement == nums[i]) min_count++;
            if (complement == nums[j]) min_count++;

            if (int_count.count(complement) > 0 && int_count[complement] >= min_count)
            {
               std::vector<int> entry = { nums[i], nums[j], complement };
               std::sort(entry.begin(), entry.end());
               ret.insert(entry);
            }
         }
      }

      return std::vector<std::vector<int>>{ ret.begin(), ret.end() };
   }

   // TODO: alternative approach: choose one element, e.g. a[i], and then do two-sum in the range a[i+1:] on target -a[i]
};

TEST_CASE("example 1")
{
   auto output = Solution().threeSum({ -1, 0, 1, 2, -1, -4 });
   auto output_set = std::set<std::vector<int>>{ output.begin(), output.end() };
   auto expected_set = std::set<std::vector<int>>{{-1, 0, 1}, { -1,-1,2 }};
   CHECK(output_set == expected_set);
}
