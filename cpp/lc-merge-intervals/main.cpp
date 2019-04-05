#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

struct Interval
{
   int start{ 0 };
   int end{ 0 };

   std::pair<int, int> toPair()
   {
      return { start, end };
   }
};


class Solution {
public:
   std::vector<Interval> merge(std::vector<Interval>& intervals)
   {
      std::sort(intervals.begin(), intervals.end(), [](const auto& i1, const auto& i2) { return i1.start < i2.start; });

      std::vector<Interval> ret;
      size_t i = 0;
      while (i < intervals.size())
      {
         Interval I = intervals[i];
         size_t j = i + 1;
         while (j < intervals.size() && I.end >= intervals[j].start)
         {
            I.end = std::max(I.end, intervals[j].end);
            j++;
         }
         ret.push_back(std::move(I));

         i = j;
      }

      return ret;
   }
};

TEST_CASE("Example1")
{
   Solution solution;
   auto input = std::vector<Interval>{ {1,3},{2,6},{8,10},{15,18} };
   auto expected = std::vector<Interval>{ {1, 6}, { 8,10 }, { 15,18 } };
   auto actual = solution.merge(input);
   REQUIRE(expected.size() == actual.size());
   for (size_t i = 0; i < expected.size(); i++)
   {
      CHECK(expected[i].toPair() == actual[i].toPair());
   }
}

TEST_CASE("Example2")
{
   Solution solution;
   auto input = std::vector<Interval>{ {1,4},{4,5} };
   auto expected = std::vector<Interval>{ {1, 5}};
   auto actual = solution.merge(input);
   REQUIRE(expected.size() == actual.size());
   for (size_t i = 0; i < expected.size(); i++)
   {
      CHECK(expected[i].toPair() == actual[i].toPair());
   }
}
