#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
   std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
      std::unordered_map<std::string, std::vector<std::string>> M;
      for (const auto& s : strs)
      {
         std::string k = s;
         std::sort(k.begin(), k.end());
         if (M.count(k) == 0)
         {
            M.emplace(k, std::vector<std::string>{});
         }
         M[k].push_back(s);
      }

      std::vector<std::vector<std::string>> ret;
      for (auto& [key, value] : M)
      {
         ret.emplace_back(std::move(value));
      }

      return ret;
   }
};

TEST_CASE("example 1")
{
  Solution solution;
  auto R = solution.groupAnagrams({ "eat", "tea", "tan", "ate", "nat", "bat" });
  CHECK(R == std::vector<std::vector<std::string>>{ { "eat", "tea", "ate" }, { "tan", "nat" }, { "bat" } });
}
