#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix)
   {
      if (matrix.empty()) return {};

      std::vector<int> R;
      traverse(matrix, 0, 0, matrix[0].size(), matrix.size(), R);

      return R;
   }

private:
   void traverse(
      const std::vector<std::vector<int>>& matrix,
      int x_origin,
      int y_origin,
      int x_width,
      int y_width,
      std::vector<int>& R
   )
   {
      if (x_width == 0 || y_width == 0)
      {
         return;
      }

      if (x_width == 1)
      {
         for (int y = y_origin; y < y_origin + y_width; y++)
         {
            R.push_back(matrix[y][x_origin]);
         }
         return;
      }
      if (y_width == 1)
      {
         for (int x = x_origin; x < x_origin + x_width; x++)
         {
            R.push_back(matrix[y_origin][x]);
         }
         return;
      }

      // assume x_width >= 2 && y_width >= 2

      // ----> x
      // |
      // |
      // V
      // y

      // x --> x
      // o     o
      // o o o o
      for (int x = x_origin; x < x_origin + x_width; x++)
      {
         const int y = y_origin;
         R.push_back(matrix[y][x]);
      }

      // o o o
      // o   x
      // o   |
      // o   v
      // o o x
      for (int y = y_origin + 1; y < y_origin + y_width; y++)
      {
         const int x = x_origin + x_width - 1;
         R.push_back(matrix[y][x]);
      }

      // o o o o o
      // o       o
      // o       o
      // x < - x o
      for (int x = x_origin + x_width - 2; x >= x_origin; x--)
      {
         const int y = y_origin + y_width - 1;
         R.push_back(matrix[y][x]);
      }

      // o o o
      // x   o
      // ^   o
      // |   o
      // x   o
      // o o o
      for (int y = y_origin + y_width - 2; y >= y_origin + 1; y--)
      {
         const int x = x_origin;
         R.push_back(matrix[y][x]);
      }

      traverse(matrix, x_origin + 1, y_origin + 1, x_width - 2, y_width - 2, R);
   }
};

TEST_CASE("example 1")
{
   CHECK(Solution().spiralOrder({ {1} }) == std::vector<int>{1});
   CHECK(Solution().spiralOrder({ {1},{2} }) == std::vector<int>{1, 2});
   CHECK(Solution().spiralOrder({ {1,2} }) == std::vector<int>{1, 2});
   CHECK(Solution().spiralOrder({ {1,2},{3,4} }) == std::vector<int>{1, 2, 4, 3});
   CHECK(Solution().spiralOrder({ {1,2,3},{4,5,6},{7,8,9} }) == std::vector<int>{1, 2, 3, 6, 9, 8, 7, 4, 5});
   CHECK(Solution().spiralOrder({ {1,2,3,4}, {5,6,7,8}, {9,10,11,12} }) == std::vector<int>{1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7});
}
