#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <map>

class Solution {
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, size_t k)
    {
       if (k == 0) return {};

       std::map<int, size_t, std::greater<int>> M;
       std::vector<int> R;

       for (size_t i = 0; i < k; i++)
       {
          if (M.count(nums[i]) == 0)
          {
             M[nums[i]] = 1;
          }
          else
          {
             M[nums[i]]++;
          }
       }

       for (size_t i = k; i < nums.size(); i++)
       {
          R.push_back(M.begin()->first);

          M[nums[i - k]]--;
          if (M[nums[i - k]] == 0)
          {
             M.erase(nums[i - k]);
          }

          if (M.count(nums[i]) == 0)
          {
             M[nums[i]] = 1;
          }
          else
          {
             M[nums[i]]++;
          }
       }
       R.push_back(M.begin()->first);

       return R;
    }
};

TEST_CASE("example 0")
{
   Solution solution;
   CHECK(solution.maxSlidingWindow({ 1,3,-1,-3,5,3,6,7 }, 3) == std::vector<int>{3, 3, 5, 5, 6, 7});
   CHECK(solution.maxSlidingWindow({ 1, -1 }, 1) == std::vector<int>{1, -1});
   CHECK(solution.maxSlidingWindow({}, 0) == std::vector<int>{});
}
