#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <set>
#include <string>

namespace
{
   std::map<size_t, std::set<std::string>> results;
}

class Solution {
public:
   std::vector<std::string> generateParenthesis(size_t n)
   {
      auto r = _generateParenthesis(n);
      r.erase("");
      return std::vector<std::string>{r.begin(), r.end()};
   }
private:
   std::set<std::string> _generateParenthesis(size_t n)
   {
      if (n == 0) return { "" };
      if (n == 1) return { "()" };
      if (results.count(n) > 0)
      {
         return results.at(n);
      }

      auto ret = std::set<std::string>{};
      // surround
      {
         auto v = _generateParenthesis(n - 1);
         for (const auto& s : v)
         {
            ret.insert("(" + s + ")");
         }
      }
      // in between
      for (size_t i = 0; i <= n - 1; i++)
      {
         auto v_before = _generateParenthesis(i);
         auto v_after = _generateParenthesis(n - 1 - i);

         for (const auto& s1 : v_before)
         {
            for (const auto& s2 : v_after)
            {
               auto s_before = "(" + s1 + ")" + s2;
               auto s_after = s1 + "(" + s2 + ")";

               ret.insert(s_before);
               ret.insert(s_after);
            }
         }
      }
      // adjacent
      for (size_t i = 1; i <= n - 1; i++)
      {
         auto v_before = _generateParenthesis(i);
         auto v_after = _generateParenthesis(n - i);

         for (const auto& s1 : v_before)
         {
            for (const auto& s2 : v_after)
            {
               ret.insert(s1 + s2);
            }
         }
      }

      results[n] = ret;
      return ret;
   }
};

TEST_CASE("example 3")
{
   Solution solution;
   CHECK(solution.generateParenthesis(3) == std::vector<std::string>{"((()))", "(()())", "(())()", "()(())", "()()()"});
}

TEST_CASE("example 4")
{
   Solution solution;
   CHECK(solution.generateParenthesis(4) == std::vector<std::string>{"(((())))", "((()()))", "((())())", "((()))()", "(()(()))", "(()()())", "(()())()", "(())(())", "(())()()", "()((()))", "()(()())", "()(())()", "()()(())", "()()()()"});
}
