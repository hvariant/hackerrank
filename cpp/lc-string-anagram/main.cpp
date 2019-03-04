#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>
#include <vector>

class Solution {
public:
   bool isAnagram(const std::string_view& s, const std::string_view& t) {
      std::vector<size_t> histogram(26, 0);
      for (char c : s)
      {
         histogram[c - 'a']++;
      }
      for (char c : t)
      {
         histogram[c - 'a']--;
      }

      return std::all_of(histogram.begin(), histogram.end(), [](auto x) { return x == 0; });
   }
};

TEST_CASE("Example1")
{
  Solution solution;
  CHECK(solution.isAnagram("anagram", "nagaram"));
}

TEST_CASE("Example2")
{
  Solution solution;
  CHECK_FALSE(solution.isAnagram("rat", "car"));
}
