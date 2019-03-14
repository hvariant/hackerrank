#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_map>
#include <limits>

// expand around centre
//class Solution {
//public:
//   std::string longestPalindrome(const std::string& s) {
//      if (s.empty()) return "";
//
//      std::pair<int, int> longest = { 0, 1 };
//      for (int i = 0; i < s.size(); i++)
//      {
//         auto odd_palindrome = expand(s, i, i);
//         if (odd_palindrome.second > longest.second)
//         {
//            longest = odd_palindrome;
//         }
//         if (s[i] == s[i + 1])
//         {
//            auto even_palindrome = expand(s, i, i + 1);
//            if (even_palindrome.second > longest.second)
//            {
//               longest = even_palindrome;
//            }
//         }
//      }
//
//      return s.substr(longest.first, longest.second);
//   }
//
//private:
//   std::pair<int, int> expand(const std::string& s, int begin, int end)
//   {
//      int i = begin, j = end;
//      while (i >= 0 && j < s.size() && s[i] == s[j])
//      {
//         i--;
//         j++;
//      }
//      i++; j--;
//
//      if (i >= j) return { begin, end - begin + 1 };
//      return { i, j - i + 1 };
//   }
//};

class Solution {
public:
   // Manacher's algorithm
   // https://tarokuriyama.com/projects/palindrome2.php
   std::vector<int> manacher(const std::string& s)
   {
      std::vector<int> P(s.size() * 2 + 1, 0);
      P[1] = 1;

      int C = 2;
      while (C < P.size())
      {
         int d = 0;
         {
            int i = (C-1) / 2;
            if (C % 2 == 0) // in-between character
            {
               d = expand(s, i, i + 1);
            }
            else // actual character
            {
               d = expand(s, i, i);
            }
         }
         P[C] = d;

         if (d == 0)
         {
            C++;
            continue;
         }

         int R = C + d;
         {
            int i;
            for (i = C + 1; i <= R; i++)
            {
               int distance_to_edge = R - i;
               int i_ = 2 * C - i;
               if (P[i_] < distance_to_edge)
               {
                  P[i] = P[i_];
               }
               else if (P[i_] > distance_to_edge)
               {
                  P[i] = distance_to_edge;
               }
               else
               {
                  break;
               }
            }
            C = i;
         }
      }

      return P;
   }

   std::string longestPalindrome(const std::string& s) {
      if (s.size() <= 1) return s;
      auto P = manacher(s);

      auto max_index = std::distance(P.begin(), std::max_element(P.begin(), P.end()));

      auto d = P[max_index];
      auto L = (max_index - d) / 2;
      return s.substr(L, d);
   }
private:
   int expand(const std::string& s, int begin, int end)
   {
      int i = begin, j = end;
      while (i >= 0 && j < s.size() && s[i] == s[j])
      {
         i--;
         j++;
      }
      if (i < j)
      {
         i++; j--;
      }

      return j - i + 1;
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
   CHECK(solution.manacher("a") == std::vector<int>{0, 1, 0});
   CHECK(solution.longestPalindrome("a") == "a");
}

TEST_CASE("Example2")
{
   Solution solution;
   CHECK(solution.manacher("cbbd") == std::vector<int>{0, 1, 0, 1, 2, 1, 0, 1, 0});
   CHECK(solution.longestPalindrome("cbbd") == "bb");
}

TEST_CASE("Example3")
{
   Solution solution;
   CHECK(solution.manacher("dabab") == std::vector<int>{0, 1, 0, 1, 0, 3, 0, 3, 0, 1, 0});
   CHECK(solution.longestPalindrome("dabab") == "aba");
}

TEST_CASE("Example4")
{
   Solution solution;
   CHECK(solution.manacher("dbbd") == std::vector<int>{0, 1, 0, 1, 4, 1, 0, 1, 0});
   CHECK(solution.longestPalindrome("dbbd") == "dbbd");
}

TEST_CASE("Example5")
{
   Solution solution;
   CHECK(solution.manacher("babab") == std::vector<int>{0, 1, 0, 3, 0, 5, 0, 3, 0, 1, 0});
   CHECK(solution.longestPalindrome("babab") == "babab");
}

TEST_CASE("Example6")
{
   Solution solution;
   CHECK(solution.manacher("cdbbdo") == std::vector<int>{0, 1, 0, 1, 0, 1, 4, 1, 0, 1, 0, 1, 0});
   CHECK(solution.longestPalindrome("cdbbdo") == "dbbd");
}

TEST_CASE("Example7")
{
   Solution solution;
   CHECK(solution.manacher("bb") == std::vector<int>{0, 1, 2, 1, 0});
   CHECK(solution.longestPalindrome("bb") == "bb");
}
