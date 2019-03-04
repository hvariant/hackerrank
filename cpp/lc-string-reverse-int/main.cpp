#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

class Solution {
public:
    int reverse(int x) {
       std::string s = std::to_string(x);
       if (s[0] == '-') // negative number
       {
          std::reverse(s.begin() + 1, s.end());
       }
       else
       {
          std::reverse(s.begin(), s.end());
       }

       try
       {
          return std::stoi(s);
       }
       catch (const std::out_of_range&)
       {
          return 0;
       }
    }
};

TEST_CASE("Example1")
{
  Solution solution;
  CHECK(solution.reverse(123) == 321);
}

TEST_CASE("Example2")
{
  Solution solution;
  CHECK(solution.reverse(-123) == -321);
}

TEST_CASE("Example3")
{
  Solution solution;
  CHECK(solution.reverse(120) == 21);
}

TEST_CASE("ExampleOverflow1")
{
  Solution solution;
  CHECK(solution.reverse(2147483647) == 0);
}

TEST_CASE("ExampleOverflow2")
{
  Solution solution;
  CHECK(solution.reverse(-2147483647) == 0);
}
