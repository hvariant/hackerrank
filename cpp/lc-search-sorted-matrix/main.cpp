#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
      if (matrix.empty()) return false;

      int i = 0, j = matrix[0].size() - 1;
      // explanation:
      // - if t < matrix[i][j], then t < matrix[i+1][j_] for all j_ > j,
      //   so no need to consider the rest of the numbers for all subsequent rows
      // - because each pointer only decreases in one direction, the time complexity
      //   is O(n)
      while (i < matrix.size() && j >= 0)
      {
         if (matrix[i][j] > target) --j;
         else if (matrix[i][j] < target) ++i;
         else return true;
      }

      return false;
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
