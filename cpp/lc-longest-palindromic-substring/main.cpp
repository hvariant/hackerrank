#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_map>
#include <limits>

// expand around centre
class Solution {
public:
   std::string longestPalindrome(const std::string& s) {
      if (s.empty()) return "";

      std::pair<int, int> longest = { 0, 1 };
      for (int i = 0; i < s.size(); i++)
      {
         auto odd_palindrome = expand(s, i, i);
         if (odd_palindrome.second > longest.second)
         {
            longest = odd_palindrome;
         }
         if (s[i] == s[i + 1])
         {
            auto even_palindrome = expand(s, i, i + 1);
            if (even_palindrome.second > longest.second)
            {
               longest = even_palindrome;
            }
         }
      }

      return s.substr(longest.first, longest.second);
   }

private:
   std::pair<int, int> expand(const std::string& s, int begin, int end)
   {
      int i = begin, j = end;
      while (i >= 0 && j < s.size() && s[i] == s[j])
      {
         i--;
         j++;
      }
      i++; j--;

      if (i >= j) return { begin, end - begin + 1 };
      return { i, j - i + 1 };
   }
};

TEST_CASE("Example null")
{
   Solution solution;
   CHECK(solution.longestPalindrome("") == "");
}

TEST_CASE("Example1")
{
   Solution solution;
   CHECK(solution.longestPalindrome("a") == "a");
}

TEST_CASE("Example2")
{
   Solution solution;
   CHECK(solution.longestPalindrome("cbbd") == "bb");
}

TEST_CASE("Example3")
{
   Solution solution;
   CHECK(solution.longestPalindrome("dabab") == "aba");
}

TEST_CASE("Example4")
{
   Solution solution;
   CHECK(solution.longestPalindrome("dbbd") == "dbbd");
}

TEST_CASE("Example5")
{
   Solution solution;
   CHECK(solution.longestPalindrome("babab") == "babab");
}

TEST_CASE("Example6")
{
   Solution solution;
   CHECK(solution.longestPalindrome("cdbbdo") == "dbbd");
}

TEST_CASE("Example7")
{
   Solution solution;
   CHECK(solution.longestPalindrome("bb") == "bb");
}
