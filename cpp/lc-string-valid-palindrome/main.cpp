#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
    bool isPalindrome(const std::string& s) {
       if (s.empty()) return true;

       size_t i = 0, j = s.size() - 1;
       while (i < j)
       {
          if (!std::isalnum(s[i]))
          {
             i++; continue;
          }
          if (!std::isalnum(s[j]))
          {
             j--; continue;
          }

          if (std::toupper(s[i]) != std::toupper(s[j])) return false;

          i++;
          j--;
       }
       return true;
    }
};

TEST_CASE("Example null")
{
  Solution solution;
  CHECK(solution.isPalindrome(""));
}

TEST_CASE("Example1")
{
  Solution solution;
  CHECK(solution.isPalindrome("A man, a plan, a canal: Panama"));
}

TEST_CASE("Example2")
{
  Solution solution;
  CHECK_FALSE(solution.isPalindrome("race a car"));
}
