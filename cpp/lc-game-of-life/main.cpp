#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   void gameOfLife(std::vector<std::vector<int>>& board) {
      for (size_t i = 0; i < board.size(); i++)
      {
         for (size_t j = 0; j < board[i].size(); j++)
         {
            size_t live_neighbours_count = 0;
            {
               int i_delta_min = i == 0 ? 0 : -1;
               int i_delta_max = i == board.size() - 1 ? 0 : 1;
               int j_delta_min = j == 0 ? 0 : -1;
               int j_delta_max = j == board[i].size() - 1 ? 0 : 1;

               for (int i_delta = i_delta_min; i_delta <= i_delta_max; i_delta++)
               {
                  for (int j_delta = j_delta_min; j_delta <= j_delta_max; j_delta++)
                  {
                     live_neighbours_count += board[i + i_delta][j + j_delta] & 1;
                  }
               }
               live_neighbours_count -= board[i][j] & 1;
            }

            if (
                  (board[i][j] && (2 <= live_neighbours_count && live_neighbours_count <= 3)) //living cell with 2-3 live neighbours
                  || (!board[i][j] && live_neighbours_count == 3) // dead cell with 3 live neighbours
               )
            {
               board[i][j] |= 2;
            }
         }
      }

      for (size_t i = 0; i < board.size(); i++)
      {
         for (size_t j = 0; j < board[i].size(); j++)
         {
            board[i][j] >>= 1;
         }
      }
   }
};

TEST_CASE("example")
{
   auto input = std::vector<std::vector<int>>{
      {0,1,0},
      {0,0,1},
      {1,1,1},
      {0,0,0}
   };
   auto expected = std::vector<std::vector<int>>{
      {0,0,0},
      {1,0,1},
      {0,1,1},
      {0,1,0}
   };

   Solution().gameOfLife(input);
   CHECK(input == expected);
}
