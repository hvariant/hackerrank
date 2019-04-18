#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
    int kthSmallest(const std::vector<std::vector<int>>& matrix, int k) {
        std::vector<int> all_items;
        for(const auto& row: matrix) {
            for(const auto& entry : row) {
                all_items.push_back(entry);
            }
        }
        std::sort(all_items.begin(), all_items.end());
        return all_items[k-1];
    }
};

TEST_CASE("example 1")
{
   Solution solution;

   auto v = std::vector<std::vector<int>>{
      {1, 5, 9},
      {10, 11, 13},
      {12, 13, 15}
   };

   CHECK(solution.kthSmallest(v, 8) == 13);
}
