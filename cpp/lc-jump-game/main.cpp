#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   bool canJump(const std::vector<int>& max_jump) {
      std::vector<bool> can_jump(max_jump.size(), false);
      can_jump[0] = true;
      for (int i = 1; i < max_jump.size(); i++)
      {
         for (int j = i - 1; j >= 0; j--)
         {
            if (can_jump[j] && max_jump[j] + j >= i)
            {
               can_jump[i] = true;
               break;
            }
         }
      }

      return can_jump.back();
   }
};

TEST_CASE("Examples")
{
   Solution solution;
   CHECK(solution.canJump({ 2,3,1,1,4 }));
   CHECK_FALSE(solution.canJump({ 3,2,1,0,4 }));
   CHECK(solution.canJump({ 2,0 }));
}
