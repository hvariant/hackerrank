#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
    // result[i] = L[i] * R[n-i-1]
    // where L[0] = 1, L[i] = nums[i] * L[i-1]
    //   and R[0] = 1, R[i] = nums[n-i] * R[i-1]
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        if(nums.size() <= 1) return nums;

        std::vector<int> result(nums.size(), 0);
        // use result to store L[i]
        {
            int from_left = 1;
            for(size_t i=0;i<nums.size();i++)
            {
                result[i] = from_left;
                from_left *= nums[i];
            }
        }

        // result[i] = L[i] * R[i]
        {
            int from_right = 1;
            for(size_t i=0;i<nums.size();i++)
            {
                size_t index = nums.size() - i - 1;
                result[index] = result[index] * from_right;
                from_right *= nums[index];
            }
        }

        return result;
    }
};

TEST_CASE("example 1")
{
    Solution solution;
    {
        std::vector<int> input = {1,2,3,4};
        CHECK(solution.productExceptSelf(input) == std::vector<int>{24,12,8,6});
    }
}
