#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> topKFrequent(const std::vector<int>& nums, size_t k) {
       std::unordered_map<int, size_t> histogram;
       for (const auto n : nums)
       {
          if (histogram.count(n) == 0)
          {
             histogram[n] = 1;
          }
          else
          {
             histogram[n]++;
          }
       }

       std::vector<int> keys;
       for (const auto& entry : histogram)
       {
          keys.push_back(entry.first);
       }

       // https://stackoverflow.com/a/32440415
       std::sort(keys.begin(), keys.end(), [&histogram = std::as_const(histogram)](auto n1, auto n2) { return histogram.at(n1) > histogram.at(n2);  });

       return std::vector<int>(keys.begin(), keys.begin() + k);
    }
};

TEST_CASE("example 1")
{
  Solution solution;
  CHECK(solution.topKFrequent({ 1 }, 1) == std::vector<int>{ 1 });
}

TEST_CASE("example 2")
{
  Solution solution;
  auto v = std::vector<int>{ 1,1,1,2,2,3 };
  CHECK(solution.topKFrequent(v, 1) == std::vector<int>{1});
  CHECK(solution.topKFrequent(v, 2) == std::vector<int>{1, 2});
  CHECK(solution.topKFrequent(v, 3) == std::vector<int>{1, 2, 3});
}

TEST_CASE("example 3")
{
  Solution solution;
  auto v = std::vector<int>{ 3,3,3,2,2,1 };
  CHECK(solution.topKFrequent(v, 1) == std::vector<int>{3});
  CHECK(solution.topKFrequent(v, 2) == std::vector<int>{3, 2});
  CHECK(solution.topKFrequent(v, 3) == std::vector<int>{3, 2, 1});
}
