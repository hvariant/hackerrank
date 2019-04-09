#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution
{
public:
    int majorityElement(const std::vector<int>& nums)
    {
        int candidate = -1;
        size_t counter = 0;

        for(auto n : nums)
        {
            // There are at least as many non-candidates
            // as candidates. If candidate is actually the majority
            // it will show up later. For now we switch to a different one.
            if(counter == 0)
            {
                candidate = n;
                counter = 1;
            }
            else
            {
                if(candidate == n)
                {
                    counter++;
                }
                else
                {
                    counter--;
                }
            }
        }

        return candidate;
    }
};

TEST_CASE("example")
{
    CHECK(Solution().majorityElement({3,2,3}) == 3);
    CHECK(Solution().majorityElement({2,2,1,1,1,2,2}) == 2);
}
