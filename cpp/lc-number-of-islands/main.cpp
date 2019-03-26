#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <queue>

class Solution {
public:
   size_t numIslands(const std::vector<std::vector<char>>& grid) {
      if (grid.empty()) return 0;

      std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

      size_t ret = 0;
      for (size_t i = 0; i < grid.size(); i++)
      {
         for (size_t j = 0; j < grid[i].size(); j++)
         {
            if (grid[i][j] == '1' && !visited[i][j])
            {
               ret++;

               std::queue<std::pair<size_t, size_t>> Q;
               Q.push({ i, j });
               visited[i][j] = true;
               while (!Q.empty())
               {
                  auto p = Q.front();
                  Q.pop();

                  // go to adjacent squares
                  if (p.first > 0 && grid[p.first - 1][p.second] == '1' && !visited[p.first - 1][p.second])
                  {
                     Q.push({ p.first - 1, p.second });
                     visited[p.first - 1][p.second] = true;
                  }
                  if (p.second > 0 && grid[p.first][p.second - 1] == '1' && !visited[p.first][p.second - 1])
                  {
                     Q.push({ p.first, p.second - 1 });
                     visited[p.first][p.second - 1] = true;
                  }
                  if (p.first < grid.size() - 1 && grid[p.first + 1][p.second] == '1' && !visited[p.first + 1][p.second])
                  {
                     Q.push({ p.first + 1, p.second });
                     visited[p.first + 1][p.second] = true;
                  }
                  if (p.second < grid[i].size() - 1 && grid[p.first][p.second + 1] == '1' && !visited[p.first][p.second + 1])
                  {
                     Q.push({ p.first, p.second + 1 });
                     visited[p.first][p.second + 1] = true;
                  }
               }
            }
         }
      }

      return ret;
   }
};

std::vector<std::vector<char>> transform_input(const std::vector<std::string>& raw)
{
   std::vector<std::vector<char>> ret;
   for (const auto& s : raw)
   {
      std::vector<char> v;
      for (const auto c : s)
      {
         v.push_back(c);
      }
      ret.push_back(std::move(v));
   }
   return ret;
}

TEST_CASE("example 0")
{
   std::vector<std::string> v_raw =
   {
      "00000",
      "00000",
      "00000",
      "00000"
   };
   std::vector<std::vector<char>> v = transform_input(v_raw);

   CHECK(Solution().numIslands(v) == 0);
}

TEST_CASE("example 1")
{
   std::vector<std::string> v_raw =
   {
      "11110",
      "11010",
      "11000",
      "00000"
   };
   std::vector<std::vector<char>> v = transform_input(v_raw);

   CHECK(Solution().numIslands(v) == 1);
}

TEST_CASE("example 2")
{
   std::vector<std::string> v_raw =
   {
      "11000",
      "11000",
      "00100",
      "00011"
   };
   std::vector<std::vector<char>> v = transform_input(v_raw);

   CHECK(Solution().numIslands(v) == 3);
}

TEST_CASE("TLE 1")
{
   std::vector<std::vector<char>> v =
   {
      { '1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','0','1','0','1','1' },
      { '0','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','0' },
      { '1','0','1','1','1','0','0','1','1','0','1','1','1','1','1','1','1','1','1','1' },
      { '1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' },
      { '1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' },
      { '1','0','1','1','1','1','1','1','0','1','1','1','0','1','1','1','0','1','1','1' },
      { '0','1','1','1','1','1','1','1','1','1','1','1','0','1','1','0','1','1','1','1' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','1','1' },
      { '1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' },
      { '0','1','1','1','1','1','1','1','0','1','1','1','1','1','1','1','1','1','1','1' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' },
      { '1','1','1','1','1','0','1','1','1','1','1','1','1','0','1','1','1','1','1','1' },
      { '1','0','1','1','1','1','1','0','1','1','1','0','1','1','1','1','0','1','1','1' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','1','1','0' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','1','0','1','1','1','1','0','0' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' },
      { '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' }
   };

   Solution().numIslands(v);
}
