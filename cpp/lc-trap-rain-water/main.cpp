#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

class Solution {
public:
    int trap(std::vector<int> const& heights) {
        if(heights.empty()) return 0;

        auto const max_elem = std::max_element(std::cbegin(heights), std::cend(heights));
        auto const rmax_elem = std::make_reverse_iterator(max_elem);
        auto ps_left = std::vector<int>();
        std::partial_sum(std::cbegin(heights), max_elem, std::back_inserter(ps_left),
                         [](auto const a, auto const b) { return std::max(a, b); });
        auto ps_right = std::vector<int>();
        std::partial_sum(std::crbegin(heights), rmax_elem, std::back_inserter(ps_right),
                         [](auto const a, auto const b) { return std::max(a, b); });

        int area_left = std::inner_product(std::cbegin(heights), max_elem, std::cbegin(ps_left), 0,
                                           std::plus{},
                                           [](auto const h, auto const m){ return std::abs(m - h); });

        int area_right = std::inner_product(std::crbegin(heights), rmax_elem, std::cbegin(ps_right), 0,
                                            std::plus{},
                                            [](auto const h, auto const m){ return std::abs(m - h); });

        return area_left + area_right;
    }
};

TEST_CASE("example 1")
{
  Solution solution;
  CHECK(solution.trap({0,1,0,2,1,0,1,3,2,1,2,1}) == 6);
}
