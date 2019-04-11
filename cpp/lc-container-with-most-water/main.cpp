#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <chrono>

class Solution {
public:
    size_t maxArea(const std::vector<int>& height) {
        if(height.size() < 2) return 0;

        size_t r = 0;
        {
            size_t i = 0, j = height.size()-1;
            // get a fast greedy solution first
            while(i < j)
            {
                size_t area = (j - i) * std::min(height[i], height[j]);
                r = std::max(area, r);

                if(height[i] > height[j])
                {
                    j--;
                }
                else
                {
                    i++;
                }
            }
        }

        // use the greedy solution to prune
        for(size_t i=0;i<height.size();i++)
        {
            if(height[i] * (height.size()-1 - i) <= r)
            {
                continue;
            }
            for(size_t j=height.size()-1;j>=i+1;j--)
            {
                if(height[j] * (j-i) <= r)
                {
                    break;
                }

                size_t area = (j - i) * std::min(height[i], height[j]);
                r = std::max(area, r);
            }
        }

        return r;
    }
};

TEST_CASE("example 0")
{
    Solution solution;
    CHECK(solution.maxArea({1}) == 0);
    CHECK(solution.maxArea({1, 2}) == 1);
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
