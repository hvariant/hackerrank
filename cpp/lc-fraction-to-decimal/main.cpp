#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <optional>
#include <map>
#include <string>

class Solution {
public:
    std::string fractionToDecimal(int numerator_signed, int denominator_signed)
    {
        if(numerator_signed == 0) return "0";
        long long numerator = std::abs(static_cast<long long>(numerator_signed));
        long long denominator = std::abs(static_cast<long long>(denominator_signed));

        // integer part
        bool is_positive = (numerator_signed > 0 && denominator_signed > 0) || (numerator_signed < 0 && denominator_signed < 0);
        std::string r = (is_positive ? "" : "-") + std::to_string(numerator / denominator);

        numerator = numerator % denominator;
        if(numerator == 0)
        {
            return r;
        }

        numerator *= 10;
        r += ".";

        std::vector<long long> V;
        std::map<std::pair<long long,long long>, size_t> seen;
        std::optional<size_t> repeat_index;
        while(numerator != 0)
        {
            if(seen.count({numerator, denominator}) > 0) // repeating
            {
                repeat_index = seen[{numerator, denominator}];
                break;
            }

            seen[{numerator, denominator}] = V.size();
            V.push_back(numerator / denominator);

            numerator = (numerator % denominator) * 10;
        }

        if(repeat_index.has_value())
        {
            for(size_t i=0;i<repeat_index.value();i++)
            {
                r += std::to_string(V[i]);
            }
            r += "(";
            for(size_t i=repeat_index.value();i < V.size();i++)
            {
                r += std::to_string(V[i]);
            }
            r += ")";
        }
        else
        {
            for(auto digit : V)
            {
                r += std::to_string(digit);
            }
        }

        return r;
    }
};

TEST_CASE("example")
{
    Solution solution;
    CHECK(solution.fractionToDecimal(1, 2) == "0.5");
    CHECK(solution.fractionToDecimal(2, 1) == "2");
    CHECK(solution.fractionToDecimal(2, 3) == "0.(6)");
    CHECK(solution.fractionToDecimal(1, 35) == "0.0(285714)");
    CHECK(solution.fractionToDecimal(1, 8) == "0.125");
    CHECK(solution.fractionToDecimal(-1, 8) == "-0.125");
}
