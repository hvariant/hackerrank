// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/646/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
  void rotate(std::vector<int>& nums, size_t k) {
    if(nums.size() <= 1){ return; }

    rotateRange(nums, 0, nums.size()-1, k % nums.size());
  }

private:
  void rotateRange(std::vector<int>& nums, size_t L, size_t U, size_t k)
  {
    size_t n = U - L + 1;
    k = k % n;

    if(U <= L || k == 0){ return; }

    if(k >= (n+1)/2)
    {
      for(size_t i=0;i<n-k;i++)
      {
        std::swap(nums[L+i], nums[L+k+i]);
      }
      rotateRange(nums, L, U-n+k, 2*k-n);
    }
    else
    {
      for(size_t i=0;i<k;i++)
      {
        std::swap(nums[L+i], nums[L+(n-k)+i]);
      }
      rotateRange(nums, L+k, U, k);
    }
  }
};

TEST_CASE("example 0")
{
  Solution solution;
  std::vector<int> nums = {1,2,3,4,5,6,7};
  solution.rotate(nums, 0);
  CHECK(nums == std::vector<int>{1,2,3,4,5,6,7});
}

TEST_CASE("example 1/7")
{
  Solution solution;
  std::vector<int> nums = {1,2,3,4,5,6,7};
  solution.rotate(nums, 1);
  CHECK(nums == std::vector<int>{7,1,2,3,4,5,6});
}

TEST_CASE("example 4/7")
{
  Solution solution;
  std::vector<int> nums = {1,2,3,4,5,6,7};
  solution.rotate(nums, 4);
  CHECK(nums == std::vector<int>{4,5,6,7,1,2,3});
}

TEST_CASE("example 6/7")
{
  Solution solution;
  std::vector<int> nums = {1,2,3,4,5,6,7};
  solution.rotate(nums, 6);
  CHECK(nums == std::vector<int>{2,3,4,5,6,7,1});
}

TEST_CASE("example 4/8")
{
  Solution solution;
  std::vector<int> nums = {1,2,3,4,5,6,7,8};
  solution.rotate(nums, 4);
  CHECK(nums == std::vector<int>{5,6,7,8,1,2,3,4});
}
