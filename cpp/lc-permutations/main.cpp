#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   std::vector<std::vector<int>> permute(const std::vector<int>& nums) {
      if (nums.empty()) return {};

      std::vector<std::vector<int>> r;
      auto items = nums;
      auto v = std::vector<int>{};
      _permute(items, 0, v, r);

      return r;
   }

private:
   void _permute(std::vector<int>& items, const size_t i, std::vector<int>& current, std::vector<std::vector<int>>& result)
   {
      if (i == items.size() - 1)
      {
         current.push_back(items.back());
         result.push_back(current);
         current.pop_back();

         return;
      }

      // original
      {
         current.push_back(items[i]);
         _permute(items, i + 1, current, result);
         current.pop_back();
      }

      // swap with subsequent items
      for (size_t j = i + 1; j < items.size(); j++)
      {
         std::swap(items[i], items[j]);
         current.push_back(items[i]);

         _permute(items, i + 1, current, result);

         current.pop_back();
         std::swap(items[i], items[j]);
      }
   }
};

TEST_CASE("example 3")
{
   auto v = Solution().permute(std::vector<int>{ 1,2,3 });

   CHECK(v == std::vector<std::vector<int>>{
      { 1, 2, 3 },
      { 1, 3, 2 },
      { 2, 1, 3 },
      { 2, 3, 1 },
      { 3, 2, 1 },
      { 3, 1, 2 },
   });
}
