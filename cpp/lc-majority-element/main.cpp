#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution
{
public:
    int majorityElement(const std::vector<int>& nums)
    {
        std::unordered_map<int, size_t> freq;
        for(auto n : nums)
        {
            if(freq.count(n) == 0)
            {
                freq[n] = 1;
            }
            else
            {
                freq[n]++;
            }

            if(freq[n] > nums.size()/2)
            {
                return n;
            }
        }

        // You may assume that the array is non-empty
        // and the majority element always exist in the array.
        return -1;
    }
};

TEST_CASE("example")
{
    CHECK(Solution().majorityElement({3,2,3}) == 3);
    CHECK(Solution().majorityElement({2,2,1,1,1,2,2}) == 2);
}
