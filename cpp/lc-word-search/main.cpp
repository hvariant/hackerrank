#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   bool exist(const std::vector<std::vector<char>>& board, const std::string& word) {
      if (word.empty()) return true;

      std::vector<std::vector<bool>> visited(board.size(), std::vector<bool>(board[0].size(), false));
      for (size_t i = 0; i < board.size(); i++)
      {
         for (size_t j = 0; j < board[i].size(); j++)
         {
            if (word[0] == board[i][j])
            {
               if (findString(board, i, j, word, visited))
               {
                  return true;
               }
            }
         }
      }
      return false;
   }

private:
   bool findString(const std::vector<std::vector<char>>& board, const size_t i, const size_t j, std::string_view word, std::vector<std::vector<bool>>& visited)
   {
      if (word.size() == 1)
      {
         return true;
      }

      visited[i][j] = true;

      std::string_view next = word;
      next.remove_prefix(1);
      if (i > 0 && !visited[i - 1][j] && next[0] == board[i - 1][j])
      {
         if (findString(board, i - 1, j, next, visited))
         {
            return true;
         }
      }
      if (j > 0 && !visited[i][j - 1] && next[0] == board[i][j - 1])
      {
         if (findString(board, i, j - 1, next, visited))
         {
            return true;
         }
      }
      if (i < board.size() - 1 && !visited[i + 1][j] && next[0] == board[i + 1][j])
      {
         if (findString(board, i + 1, j, next, visited))
         {
            return true;
         }
      }
      if (j < board[i].size() - 1 && !visited[i][j + 1] && next[0] == board[i][j + 1])
      {
         if (findString(board, i, j + 1, next, visited))
         {
            return true;
         }
      }
      visited[i][j] = false;

      return false;
   }
};

TEST_CASE("example 1")
{
   auto board = std::vector<std::vector<char>>{
      {'A','B','C','E'},
      {'S','F','C','S'},
      {'A','D','E','E'}
   };

   Solution solution;
   CHECK(solution.exist(board, ""));
   CHECK(solution.exist(board, "ABCCED"));
   CHECK(solution.exist(board, "SEE"));
   CHECK_FALSE(solution.exist(board, "ABCB"));
}
