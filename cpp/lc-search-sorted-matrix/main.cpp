#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
      size_t i = 0;

      return std::any_of(matrix.begin(), matrix.end(), [target](const auto& row)
      {
         return std::binary_search(row.begin(), row.end(), target);
      });
   }
};

TEST_CASE("Example")
{
   Solution solution;
   std::vector<std::vector<int>> input = {
      {1, 4, 7, 11, 15},
      {2, 5, 8, 12, 19},
      {3, 6, 9, 16, 22},
      {10, 13, 14, 17, 24},
      {18, 21, 23, 26, 30}
   };

   CHECK(solution.searchMatrix(input, 5));
   CHECK_FALSE(solution.searchMatrix(input, 20));
}
