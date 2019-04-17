#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <string>
#include <string_view>

class Solution {
public:
    std::vector<std::vector<std::string>> partition(std::string_view s)
    {
       std::vector<std::string> cur;
       std::vector<std::vector<std::string>> result;

       _partition(s, cur, result);

       return result;
    }

private:
   bool isPalindrome(std::string_view s)
   {
      for (size_t i = 0; i < s.length()/2; i++)
      {
         if (s[i] != s[s.length() - i - 1])
         {
            return false;
         }
      }
      return true;
   }

   void _partition(std::string_view s, std::vector<std::string>& current, std::vector<std::vector<std::string>>& result)
   {
      if (s.empty())
      {
         result.push_back(current);
         return;
      }

      for (size_t i = 1; i <= s.length(); i++)
      {
         auto s_first = s.substr(0, i);
         if (isPalindrome(s_first))
         {
            current.push_back(std::string(s_first));
            auto s_rest = s;
            s_rest.remove_prefix(i);

            _partition(s_rest, current, result);

            current.pop_back();
         }
      }
   }
};

TEST_CASE("Example")
{
   Solution solution;
   CHECK(solution.partition("aab") == std::vector<std::vector<std::string>>{{ "a", "a", "b" }, {"aa", "b"}});
}
