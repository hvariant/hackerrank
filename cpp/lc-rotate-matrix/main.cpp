#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
  void rotate(std::vector<std::vector<int>>& matrix) {
    const size_t N = matrix.size();
    for(size_t l = 0; l < N/2;l++)
    {
      const size_t x0 = l;
      const size_t y0 = l;
      const size_t xn = x0 + N - 2*l - 1;
      const size_t yn = y0 + N - 2*l - 1;

      for(size_t i=0;i < N - 2*l - 1;i++)
      {
        // a -> b -> c -> d -> a
        // a : [x0][y0+i]
        // b : [x0+i][yn]
        // c : [xn][yn-i]
        // d : [xn-i][y0]
        int& a = matrix[x0][y0+i];
        int& b = matrix[x0+i][yn];
        int& c = matrix[xn][yn-i];
        int& d = matrix[xn-i][y0];

        int t = a;
        a = d;
        d = c;
        c = b;
        b = t;
      }
    }
  }
};

TEST_CASE("example 1")
{
  std::vector<std::vector<int>> v =
  {
    {1,2,3},
    {4,5,6},
    {7,8,9}
  };
  std::vector<std::vector<int>> expected =
  {
    {7,4,1},
    {8,5,2},
    {9,6,3}
  };

  Solution().rotate(v);
  CHECK(v == expected);
}

TEST_CASE("example 2")
{
  std::vector<std::vector<int>> v =
  {
    { 5, 1, 9,11},
    { 2, 4, 8,10},
    {13, 3, 6, 7},
    {15,14,12,16}
  };
  std::vector<std::vector<int>> expected =
  {
    {15,13, 2, 5},
    {14, 3, 4, 1},
    {12, 6, 8, 9},
    {16, 7,10,11}
  };

  Solution().rotate(v);
  CHECK(v == expected);
}

TEST_CASE("example 3")
{
  std::vector<std::vector<int>> v =
  {
    {1,2,3,4,5},
    {6,7,8,9,10},
    {11,12,13,14,15},
    {16,17,18,19,20},
    {21,22,23,24,25}
  };
  std::vector<std::vector<int>> expected =
  {
    {21,16,11,6,1},
    {22,17,12,7,2},
    {23,18,13,8,3},
    {24,19,14,9,4},
    {25,20,15,10,5}
  };

  Solution().rotate(v);
  CHECK(v == expected);
}
