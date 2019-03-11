// https://leetcode.com/explore/interview/card/top-interview-questions-easy/96/sorting-and-searching/587/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <set>

class Solution {
public:
   // using O(m+n) space
   //void setZeroes(std::vector<std::vector<int>>& matrix) {
   //   std::set<size_t> zero_rows;
   //   std::set<size_t> zero_cols;

   //   for (size_t i = 0; i < matrix.size(); i++)
   //   {
   //      for (size_t j = 0; j < matrix[i].size(); j++)
   //      {
   //         if (matrix[i][j] == 0)
   //         {
   //            zero_cols.insert(j);
   //            zero_rows.insert(i);
   //         }
   //      }
   //   }

   //   for (const auto i : zero_rows)
   //   {
   //      for (size_t j = 0; j < matrix[i].size(); j++)
   //      {
   //         matrix[i][j] = 0;
   //      }
   //   }
   //   for (const auto j : zero_cols)
   //   {
   //      for (size_t i = 0; i < matrix.size(); i++)
   //      {
   //         matrix[i][j] = 0;
   //      }
   //   }
   //}

   // use first row and column to remember zeroes
   // need to remember whether first row/column needs to be set to all zero
   void setZeroes(std::vector<std::vector<int>>& matrix) {
      if (matrix.size() == 0) return;

      // first row and column
      bool first_row_zero = std::any_of(matrix[0].begin(), matrix[0].end(), [](auto x) { return x == 0; });
      bool first_column_zero = std::any_of(matrix.begin(), matrix.end(), [](const auto& row) { return row[0] == 0; });

      // rest of the rows & columns
      for (size_t i = 1; i < matrix.size(); i++)
      {
         for (size_t j = 1; j < matrix[i].size(); j++)
         {
            if (matrix[i][j] == 0)
            {
               matrix[i][0] = 0;
               matrix[0][j] = 0;
            }
         }
      }

      for (size_t i = 1; i < matrix.size(); i++)
      {
         if (matrix[i][0] == 0)
         {
            for (size_t j = 0; j < matrix[i].size(); j++)
            {
               matrix[i][j] = 0;
            }
         }
      }
      for (size_t j = 1; j < matrix[0].size(); j++)
      {
         if (matrix[0][j] == 0)
         {
            for (size_t i = 0; i < matrix.size(); i++)
            {
               matrix[i][j] = 0;
            }
         }
      }

      if (first_row_zero)
      {
         for (size_t j = 0; j < matrix[0].size(); j++)
         {
            matrix[0][j] = 0;
         }
      }
      if (first_column_zero)
      {
         for (size_t i = 0; i < matrix.size(); i++)
         {
            matrix[i][0] = 0;
         }
      }
   }
};

TEST_CASE("example 1")
{
  Solution solution;
  std::vector<std::vector<int>> input = {
     {1,1,1},
     {1,0,1},
     {1,1,1}
  };
  std::vector<std::vector<int>> expected = {
     {1,0,1},
     {0,0,0},
     {1,0,1}
  };

  solution.setZeroes(input);
  CHECK(input == expected);
}

TEST_CASE("example 2")
{
  Solution solution;
  std::vector<std::vector<int>> input = {
     {0,1,2,0},
     {3,4,5,2},
     {1,3,1,5}
  };
  std::vector<std::vector<int>> expected = {
     {0,0,0,0},
     {0,4,5,0},
     {0,3,1,0}
  };

  solution.setZeroes(input);
  CHECK(input == expected);
}
