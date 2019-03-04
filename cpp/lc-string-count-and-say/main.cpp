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

TEST_CASE("Example 1")
{
   CHECK(true);
}
