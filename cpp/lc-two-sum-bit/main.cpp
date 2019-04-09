// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/578/

#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
    int getSum(int a_signed, int b_signed)
    {
        unsigned int a = static_cast<unsigned int>(a_signed);
        unsigned int b = static_cast<unsigned int>(b_signed);

        unsigned int r = 0;
        unsigned int bit_flag = 1;
        int carry = 0;
        while(a || b)
        {
            int a_bit = a & 1;
            int b_bit = b & 1;

            int val = a_bit ^ b_bit ^ carry;
            carry = (a_bit && b_bit) || (a_bit && carry) || (b_bit && carry);

            if(val)
            {
                r = r | bit_flag;
            }

            a >>= 1;
            b >>= 1;
            if(a || b)
            {
                bit_flag <<= 1;
            }
        }

        if(carry)
        {
            if(bit_flag < std::numeric_limits<unsigned int>::max())
            {
                bit_flag <<= 1;
                r = r | bit_flag;
            }
        }

        return static_cast<int>(r);
    }
};

TEST_CASE("example")
{
    CHECK(Solution().getSum(1,2) == 3);
    CHECK(Solution().getSum(-2,3) == 1);
    CHECK(Solution().getSum(2,3) == 5);
    CHECK(Solution().getSum(std::numeric_limits<int>::max(),std::numeric_limits<int>::max()) == (std::numeric_limits<int>::max() + std::numeric_limits<int>::max()));
}
