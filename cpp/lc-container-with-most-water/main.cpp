#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <chrono>

class Solution {
public:
    int maxArea(const std::vector<int>& height) {
        size_t r = 0;
        for(size_t i=0;i<height.size();i++)
        {
            for(size_t j=height.size()-1;j>=i+1;j--)
            {
                // pruning
                if(height[i] * (j-i) <= r)
                {
                    break;
                }

                size_t area = (j-i) * std::min(height[i], height[j]);

                if(area > r)
                {
                    r = area;
                }
            }
        }
        return r;
    }
};

TEST_CASE("example 0")
{
    Solution solution;
    CHECK(solution.maxArea({1,8,6,2,5,4,8,3,7}) == 49);
    CHECK(solution.maxArea({2,3,4,5,18,17,6}) == 17);
}

TEST_CASE("TLE")
{
    std::vector<int> input;
    for(size_t i=15000; i>=1;i--)
    {
        input.push_back(i);
    }

    {
        auto begin = std::chrono::high_resolution_clock::now();

        Solution solution;
        (void)solution.maxArea(input);

        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        CHECK(dur < 1000);
    }
}
