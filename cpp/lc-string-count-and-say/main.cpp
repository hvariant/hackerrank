#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// haskell solution:
// mergeSame :: [(Char,Int)] -> Char -> [(Char,Int)]
// mergeSame t@((x',c):t') x =
//     if x == x'
//     then (x,c+1):t'
//     else (x,1):t
// 
// count :: String -> [(Char,Int)]
// count "" = []
// count (x:xs) = reverse $ foldl mergeSame [(x,1)] xs
// 
// say :: [(Char,Int)] -> String
// say [] = ""
// say ((x,c):xs) = (show c) ++ [x] ++ (say xs)
// 
// sayAndCount :: Int -> String
// sayAndCount n = iterate (say . count) "1" !! n

// It might be possible to translate this into C++ TMP,
// but I'm not in the mood for this right now.

class Solution {
public:
    std::string countAndSay(int n) {
       std::string r = "1";
       for (size_t _i = 1; _i < n; _i++)
       {
          std::string r_;
          size_t i = 0;
          while (i < r.size())
          {
             auto p = count(r, i);
             r_.append(std::to_string(p.second));
             r_.append(1, p.first);
          }
          r = std::move(r_);
       }
       return r;
    }

private:
   std::pair<char, size_t> count(std::string_view s, size_t& i)
   {
      size_t j = i + 1;
      while (j < s.size() && s[j] == s[i])
      {
         j++;
      }

      char c = s[i];
      size_t len = j - i;
      i = j;

      return { c, len };
   }
};

TEST_CASE("Example 1")
{
   Solution solution;
   CHECK(solution.countAndSay(1) == "1");
}

TEST_CASE("Example 4")
{
   Solution solution;
   CHECK(solution.countAndSay(4) == "1211");
}

