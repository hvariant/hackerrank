#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_map>

class Solution {
public:
   size_t fourSumCount(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C, std::vector<int>& D)
   {
      std::unordered_map<int, size_t> AB, CD;
      for (auto a : A)
      {
         for (auto b : B)
         {
            if (AB.count(a + b) == 0)
            {
               AB[a + b] = 1;
            }
            else
            {
               AB[a + b]++;
            }
         }
      }
      for (auto c : C)
      {
         for (auto d : D)
         {
            if (CD.count(c + d) == 0)
            {
               CD[c + d] = 1;
            }
            else
            {
               CD[c + d]++;
            }
         }
      }

      size_t R = 0;
      for (auto ab : AB)
      {
         if (CD.count(-ab.first) != 0)
         {
            R += ab.second * CD.at(-ab.first);
         }
      }

      return R;
   }
};

TEST_CASE("example 1")
{
   {
      auto A = std::vector<int>{ 1,2 };
      auto B = std::vector<int>{ -2,-1 };
      auto C = std::vector<int>{ -1,2 };
      auto D = std::vector<int>{ 0,2 };

      CHECK(Solution().fourSumCount(A, B, C, D) == 2);
   }

   {
      auto A = std::vector<int>{0,1,-1};
      auto B = std::vector<int>{-1,1,0};
      auto C = std::vector<int>{0,0,1};
      auto D = std::vector<int>{-1,1,1};

      CHECK(Solution().fourSumCount(A, B, C, D) == 17);
   }
}
