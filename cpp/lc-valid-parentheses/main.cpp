// https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/721/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <stack>

class Solution {
public:
  bool isValid(const std::string& s)
  {
    if(s.empty()) return true;

    size_t i=0;
    std::stack<char> S;

    S.push(s[i++]);
    while(i < s.length())
    {
      char cur = s[i];

      if(S.empty())
      {
        S.push(cur);
      }
      else if(paired(S.top(), cur))
      {
        S.pop();
      }
      else
      {
        S.push(cur);
      }

      i++;
    }

    return S.empty();
  }

private:
  bool paired(char left, char right)
  {
    if(left == '{') return right == '}';
    if(left == '(') return right == ')';
    if(left == '[') return right == ']';
    return false;
  }
};

TEST_CASE("example 0")
{
  Solution solution;
  CHECK(solution.isValid("") == true);
}

TEST_CASE("example 1")
{
  Solution solution;
  CHECK(solution.isValid("()") == true);
}

TEST_CASE("example 2")
{
  Solution solution;
  CHECK(solution.isValid("()[]{}") == true);
}

TEST_CASE("example 3")
{
  Solution solution;
  CHECK(solution.isValid("(]") == false);
}

TEST_CASE("example 4")
{
  Solution solution;
  CHECK(solution.isValid("([)]") == false);
}

TEST_CASE("example 5")
{
  Solution solution;
  CHECK(solution.isValid("{[]}") == true);
}
