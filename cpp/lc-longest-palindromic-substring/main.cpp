#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_map>
#include <limits>

class Solution {
public:
   std::string longestPalindrome(const std::string& s) {
      if (s.empty()) return "";

      std::string s_odd = longestOddPallinDrome(s), s_even = longestEvenPalindrome(s);
      return s_odd.size() > s_even.size() ? s_odd : s_even;
   }
private:
   std::string longestEvenPalindrome(const std::string& s)
   {
      const size_t dummy_index = std::numeric_limits<size_t>::max();
      size_t max_index = dummy_index, max_offset = 0;
      for (size_t index = 0; index < s.size() - 1; index++)
      {
         if (s[index] != s[index + 1]) continue;
         size_t offset = 0;
         for (;
            index >= offset && index + 1 + offset < s.size() && s[index - offset] == s[index + 1 + offset];
            offset++)
         {
         }
         if (offset > 0)
         {
            offset--;
         }

         if (max_index == dummy_index || offset > max_offset)
         {
            max_offset = offset;
            max_index = index;
         }
      }
      if (max_index == dummy_index) return "";
      size_t start_index = max_index - max_offset;
      size_t max_size = max_offset * 2 + 2;
      return s.substr(start_index, max_size);
   }
   std::string longestOddPallinDrome(const std::string& s)
   {
      size_t max_index = 0, max_offset = 0;
      for (size_t index = 1; index < s.size() - 1; index++)
      {
         size_t offset = 0;
         for (;
            index >= offset && index + offset < s.size() && s[index - offset] == s[index + offset];
            offset++)
         {
         }
         if (offset > 0)
         {
            offset--;
         }

         if (offset > max_offset)
         {
            max_offset = offset;
            max_index = index;
         }
      }
      size_t start_index = max_index - max_offset;
      size_t substr_size = max_offset * 2 + 1;
      return s.substr(start_index, substr_size);
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

