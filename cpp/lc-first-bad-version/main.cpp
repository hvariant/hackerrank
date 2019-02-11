// https://leetcode.com/explore/interview/card/top-interview-questions-easy/96/sorting-and-searching/774/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
  int firstBadVersion(int n)
  {
    return findFirstBad(1, n);
  }

private:
  int findFirstBad(int L, int U)
  {
    if(L == U)
    {
      return L;
    }
    if(U - L == 1)
    {
      return isBadVersion(L) ? L : U;
    }

    int M = static_cast<int>((static_cast<long long>(L)+static_cast<long long>(U))/2);
    if(isBadVersion(M))
    {
      return findFirstBad(L, M);
    }
    else
    {
      return findFirstBad(M, U);
    }
  }
};

namespace
{
  size_t call_counter = 0;
  int first_bad = 4;
}

bool isBadVersion(int version)
{
  call_counter++;
  return first_bad <= version;
}

TEST_CASE("example")
{
  call_counter = 0;
  first_bad = 4;

  Solution solution;
  CHECK(solution.firstBadVersion(5) == first_bad);
  CHECK(call_counter == 3);
}
