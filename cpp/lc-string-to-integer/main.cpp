#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <limits>

class Solution {
public:
    int myAtoi(const std::string& s) {
       std::string stripped;
       size_t i = 0;
       // skip initial ' 's
       while(i < s.size() && s[i] == ' ') ++i;
       // optional initial sign
       if (i < s.size())
       {
          if (s[i] == '+')
          {
             stripped.push_back('+');
             i++;
          }
          else if(s[i] == '-')
          {
             stripped.push_back('-');
             i++;
          }
       }
       // rest of the numbers
       for (; i < s.size() && std::isdigit(s[i]); i++)
       {
          stripped.push_back(s[i]);
       }

       if (stripped.empty())
       {
          return 0;
       }
       if (stripped == "+" || stripped == "-")
       {
          return 0;
       }

       try
       {
          return std::stoi(stripped);
       }
       catch (const std::out_of_range&)
       {
          if (stripped[0] == '-')
          {
             return std::numeric_limits<int>::min();
          }
          else
          {
             return std::numeric_limits<int>::max();
          }
       }
    }
};

TEST_CASE("Example null 1")
{
  Solution solution;
  CHECK(solution.myAtoi("") == 0);
}

TEST_CASE("Example null 2")
{
  Solution solution;
  CHECK(solution.myAtoi("-") == 0);
}

TEST_CASE("Example null 3")
{
  Solution solution;
  CHECK(solution.myAtoi("+") == 0);
}

TEST_CASE("Example 1")
{
  Solution solution;
  CHECK(solution.myAtoi("42") == 42);
}

TEST_CASE("Example 2")
{
  Solution solution;
  CHECK(solution.myAtoi("   -42") == -42);
}

TEST_CASE("Example 3")
{
  Solution solution;
  CHECK(solution.myAtoi("4193 with words") == 4193);
}

TEST_CASE("Example 4")
{
  Solution solution;
  CHECK(solution.myAtoi("words and 987") == 0);
}

TEST_CASE("Example 5")
{
  Solution solution;
  CHECK(solution.myAtoi("-91283472332") == std::numeric_limits<int>::min());
}
