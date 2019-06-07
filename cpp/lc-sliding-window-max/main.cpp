#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <queue>

class Solution {
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, size_t k)
    {
       if (k == 0) return {};

       std::deque<size_t> Q;
       std::vector<int> R;

       for (size_t i = 0; i < k; i++)
       {
          // remove less worthy numbers
          while (!Q.empty() && nums[i] >= nums[Q.back()]) Q.pop_back();
          Q.push_back(i);
       }

       for (size_t i = k; i < nums.size(); i++)
       {
          R.push_back(nums[Q.front()]);

          // remove expired numbers
          while (!Q.empty() && Q.front() <= i - k) Q.pop_front();

          // remove less worthy numbers
          while (!Q.empty() && nums[i] >= nums[Q.back()]) Q.pop_back();

          Q.push_back(i);
       }
       R.push_back(nums[Q.front()]);

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
