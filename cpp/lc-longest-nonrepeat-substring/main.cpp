#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_map>

class Solution {
public:
   int lengthOfLongestSubstring(const std::string& s) {
      if (s.empty()) return 0;

      std::unordered_map<char, bool> char_count;

      char_count[s[0]] = true;
      int longest = 1;
      int i = 0, j = 1;
      while (i < s.size() && j < s.size())
      {
         // try to grow
         if (char_count.count(s[j]) == 0 || !char_count.at(s[j]))
         {
            char_count[s[j]] = true;
            j++;

            if (j - i > longest)
            {
               longest = j - i;
            }
         }
         // try to shrink
         else
         {
            char_count[s[i]] = false;
            i++;
         }
      }

      return longest;
   }
};

TEST_CASE("Example null")
{
   Solution solution;
   CHECK(solution.lengthOfLongestSubstring("") == 0);
}

TEST_CASE("Example1")
{
   Solution solution;
   CHECK(solution.lengthOfLongestSubstring("abcabcbb") == 3);
}

TEST_CASE("Example2")
{
   Solution solution;
   CHECK(solution.lengthOfLongestSubstring("bbbbb") == 1);
}

TEST_CASE("Example3")
{
   Solution solution;
   CHECK(solution.lengthOfLongestSubstring("pwwkew") == 3);
}

