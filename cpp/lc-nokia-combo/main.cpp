#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <string>
#include <string_view>

namespace {
   const std::map<char, std::string> digit_map = {
      {'2', "abc"},
      {'3', "def"},
      {'4', "ghi"},
      {'5', "jkl"},
      {'6', "mno"},
      {'7', "pqrs"},
      {'8', "tuv"},
      {'9', "wxyz"},
   };
}

class Solution {
public:
   std::vector<std::string> letterCombinations(std::string_view digits)
   {
      std::vector<std::string> ret;
      search(digits, "", ret);

      return ret;
   }

private:
   void search(std::string_view digits, const std::string& s, std::vector<std::string>& ret)
   {
      if (digits.empty())
      {
         if (!s.empty())
         {
            ret.push_back(s);
         }
      }
      else
      {
         for (char c : digit_map.at(digits[0]))
         {
            std::string s_next = s;
            s_next.append(1, c);
            std::string_view digits_next = digits;
            digits_next.remove_prefix(1);

            search(digits_next, s_next, ret);
         }
      }
   }
};

TEST_CASE("example 0")
{
  Solution solution;
  CHECK(solution.letterCombinations("23") == std::vector<std::string>{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"});
}

TEST_CASE("null 0")
{
   Solution solution;
   CHECK(solution.letterCombinations("").empty());
}
