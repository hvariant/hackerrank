// https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/601/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

using std::vector;

class Solution {
public:
  vector<vector<int>> generate(size_t numRows) {
    if(numRows == 0) return {};

    vector<vector<int>> R = {{1}};
    if(numRows >= 2)
    {
      R.emplace_back(vector<int>{1,1});
    }
    for(size_t i=2;i<numRows;i++)
    {
      vector<int> row(i+1, 0);
      row.front() = 1;
      row.back() = 1;

      for(size_t j=1;j<=i-1;j++)
      {
        row[j] = R[i-1][j] + R[i-1][j-1];
      }

      R.emplace_back(row);
    }

    return R;
  }
};

TEST_CASE("example 0")
{
  Solution solution;
  CHECK(solution.generate(0) == vector<vector<int>>{});
}

TEST_CASE("example 1")
{
  Solution solution;
  CHECK(solution.generate(1) == vector<vector<int>>{{1}});
}

TEST_CASE("example 5")
{
  Solution solution;
  CHECK(solution.generate(5) == vector<vector<int>>{{1}, {1,1}, {1,2,1}, {1,3,3,1}, {1,4,6,4,1}});
}
