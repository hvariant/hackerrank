#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   std::vector<std::vector<int>> subsets(const std::vector<int>& nums)
   {
      if (nums.empty()) return { {} };

      std::vector<std::vector<int>> r;
      std::vector<int> current;
      findSubsets(nums, 0, current, r);

      return r;
   }

private:
   void findSubsets(const std::vector<int>& items, size_t index, std::vector<int>& current, std::vector<std::vector<int>>& results)
   {
      if (index == items.size())
      {
         results.push_back(current);
         return;
      }

      // with items[index]
      findSubsets(items, index + 1, current, results);

      // without items[index]
      current.push_back(items[index]);
      findSubsets(items, index + 1, current, results);
      current.pop_back();
   }
};

TEST_CASE("example 3")
{
   auto v = Solution().subsets(std::vector<int>{ 1,2,3 });

   CHECK(v.size() == std::vector<std::vector<int>>{
      { 3 },
      { 1 },
      { 2 },
      { 1, 2, 3 },
      { 1, 3 },
      { 2, 3 },
      { 1, 2 },
      { },
   }.size());
}
