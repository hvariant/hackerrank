#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_set>
#include <queue>

class Solution {
public:
    int ladderLength(
       const std::string& beginWord,
       const std::string& endWord,
       const std::vector<std::string>& wordList)
    {
       auto wordSet = std::unordered_set<std::string>(wordList.begin(), wordList.end());
       if (wordSet.count(endWord) > 0)
       {
          return ladderLengthBFS(beginWord, endWord, wordSet);
       }
       else
       {
          return 0;
       }
    }

private:
   int ladderLengthBFS(
      const std::string& beginWord,
      const std::string& endWord,
      const std::unordered_set<std::string>& wordSet)
   {
      std::unordered_set<std::string> vs;
      std::queue<std::pair<std::string, int>> Q;

      Q.push({ beginWord, 0 });
      while (!Q.empty())
      {
         auto cur = Q.front();
         Q.pop();

         vs.insert(cur.first);

         if (cur.first == endWord)
         {
            return cur.second + 1;
         }

         std::string next = cur.first;
         for (size_t i = 0; i < next.length(); i++)
         {
            auto original_c = next[i];
            for(char c = 'a'; c <= 'z'; c++)
            {
               next[i] = c;
               if (wordSet.count(next) > 0 && vs.count(next) == 0)
               {
                  Q.push({ next, cur.second + 1 });
               }
            }
            next[i] = original_c;
         }
      }

      return 0;
   }
};

TEST_CASE("example")
{
   Solution solution;
   CHECK(solution.ladderLength("hit", "cog", { "hot","dot","dog","lot","log","cog" }) == 5);
   CHECK(solution.ladderLength("hit", "cog", { "hot","dot","dog","lot","log" }) == 0);
   CHECK(solution.ladderLength("hit", "hot", { "hot","dot","dog","lot","log" }) == 2);
   CHECK(solution.ladderLength("hit", "neg", { "hot","mot","mog","nog","neg" }) == 6);
}
