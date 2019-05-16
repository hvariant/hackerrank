#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_map>
#include <unordered_set>
#include <queue>

class Solution {
public:
    size_t ladderLength(
       const std::string& beginWord,
       const std::string& endWord,
       const std::vector<std::string>& wordList)
    {
       // endWord not on the list
       auto endWordIter = std::find(wordList.begin(), wordList.end(), endWord);
       if (endWordIter == wordList.end())
       {
          return 0;
       }
       size_t endWord_index = std::distance(wordList.begin(), endWordIter);

       // no need to transform at all
       if (endWord == beginWord)
       {
          return 1;
       }

       // map strings to integer to make them more memory efficient
       auto allWords = wordList;
       allWords.push_back(beginWord);
       std::unordered_map<std::string, size_t> str_to_index;
       for (size_t i = 0; i < allWords.size(); i++)
       {
          str_to_index[allWords[i]] = i;
       }

       std::unordered_set<size_t> vs;
       auto Q = std::queue<std::pair<size_t, size_t>>{};
       Q.push({ allWords.size() - 1, 1 });
       vs.insert(allWords.size() - 1);
       while (!Q.empty())
       {
          auto cur = Q.front();
          Q.pop();

          if (cur.first == endWord_index)
          {
             return cur.second;
          }

          auto next = allWords[cur.first];
          auto next_step = cur.second + 1;
          for (size_t i = 0; i < next.length(); i++)
          {
             auto original_c = next[i];
             for (char c = 'a'; c <= 'z'; c++)
             {
                next[i] = c;
                if (str_to_index.count(next) > 0)
                {
                   auto next_index = str_to_index.at(next);
                   if (vs.count(next_index) == 0)
                   {
                      vs.insert(next_index);
                      Q.push({ next_index, next_step });
                   }
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
