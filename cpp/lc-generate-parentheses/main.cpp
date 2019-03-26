#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <string>
#include <queue>

class Solution {
public:
   std::vector<std::string> generateParenthesis(size_t n)
   {
      if (n == 0) return {};

      struct S
      {
         size_t open;
         size_t close;
         std::string current;
      };

      std::vector<std::string> ret;

      // this will put all sequences that maintain
      //    cur.open >= cur.close for all positions
      // to the return list
      std::queue<S> Q;
      Q.push({ 0, 0, "" });
      while (!Q.empty())
      {
         auto cur = Q.front();
         Q.pop();

         if (cur.open == n && cur.close == n)
         {
            ret.push_back(cur.current);
         }
         if (cur.open < n)
         {
            Q.push({ cur.open + 1, cur.close, cur.current + "(" });
         }
         if (cur.close < n && cur.open > cur.close)
         {
            Q.push({ cur.open, cur.close + 1, cur.current + ")" });
         }
      }

      return ret;
   }
};

TEST_CASE("example 0")
{
   Solution solution;
   CHECK(solution.generateParenthesis(0).empty());
}

TEST_CASE("example 1")
{
   Solution solution;
   CHECK(solution.generateParenthesis(1) == std::vector<std::string>{"()"});
}

TEST_CASE("example 2")
{
   Solution solution;
   CHECK(solution.generateParenthesis(2) == std::vector<std::string>{"(())", "()()"});
}

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
