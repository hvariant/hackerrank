#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Solution {
public:
   size_t fourSumCount(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C, std::vector<int>& D)
   {
      std::sort(A.begin(), A.end());
      std::sort(B.begin(), B.end());
      std::sort(C.begin(), C.end());
      std::sort(D.begin(), D.end());

      size_t R{ 0 };

      for (size_t A_i = 0; A_i < A.size(); A_i++)
      {
         for (size_t B_i = 0; B_i < B.size(); B_i++)
         {
            int goal = -(A[A_i] + B[B_i]);

            int i = 0;
            int j = D.size() - 1;
            while (j >= 0 && i < D.size())
            {
               if (C[i] + D[j] == goal)
               {
                  size_t dup_C{ 0 };
                  int i_next{ i };
                  while (i_next < C.size() && C[i] == C[i_next]) i_next++;
                  dup_C = i_next - i;

                  size_t dup_D{ 0 };
                  int j_next{ j };
                  while (j_next >= 0 && D[j] == D[j_next]) j_next--;
                  dup_D = j - j_next;
                  
                  // rule of product
                  R += dup_D * dup_C;

                  // at this point we can advance either i or j
                  i = i_next;
               }
               else if (C[i] + D[j] > goal)
               {
                  j--;
               }
               else
               {
                  i++;
               }
            }
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
