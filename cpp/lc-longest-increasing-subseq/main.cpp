#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   // https://www.sciencedirect.com/science/article/pii/S0890540110000647
   // this is the previous best algorithm
   size_t lengthOfLIS(const std::vector<int>& nums)
   {
      if (nums.empty()) return 0;

      std::vector<int> B;
      B.push_back(nums[0]);

      for (size_t i = 1; i < nums.size(); i++)
      {
         if (nums[i] > B.back())
         {
            B.push_back(nums[i]);
         }
         // find succ(B, nums[i]), i.e. the smallest element that is larger than or equal to nums[i],
         // and then replace it with nums[i]
         else
         {
            int succ_index = -1;
            int left = 0, right = B.size() - 1;

            // loop-invariant: B[left] < nums[i] && nums[i] <= B[right]
            while (left < right)
            {
               if (left + 1 == right)
               {
                  if (B[left] >= nums[i]) right = left;
                  break;
               }

               int mid = (right - left) / 2 + left;
               if (B[mid] < nums[i])
               {
                  left = mid;
               }
               else if(B[mid] > nums[i])
               {
                  right = mid;
               }
               else
               {
                  right = mid;
                  break;
               }
            }
            succ_index = right;

            B[succ_index] = nums[i];
         }
      }

      return B.size();
   }
};

TEST_CASE("Example null")
{
   Solution solution;
   CHECK(solution.lengthOfLIS({}) == 0);
}

TEST_CASE("Example1")
{
   Solution solution;
   CHECK(solution.lengthOfLIS({ 10,9,2,5,3,7,101,18 }) == 4);
   CHECK(solution.lengthOfLIS({ 4,10,4,3,8,9 }) == 3);
}
