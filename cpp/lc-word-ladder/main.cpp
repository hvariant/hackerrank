#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_map>
#include <unordered_set>
#include <queue>

// a wild solution stolen from leetcode 24 ms sample submission,
// I merely made it look better

class Solution {
public:
   size_t ladderLength(
      const std::string& beginWord,
      const std::string& endWord,
      const std::vector<std::string>& wordList)
   {
      std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
      if (wordSet.count(endWord) == 0) return 0;

      std::unordered_set<std::string> head{ beginWord };
      std::unordered_set<std::string> tail{ endWord };

      size_t steps = 1;
      // alternate between front and back
      while (head.size())
      {
         steps++;

         std::unordered_set<std::string> frontier;
         for (auto str : head)
         {
            wordSet.erase(str);

            for (size_t i = 0; i < str.size(); i++)
            {
               auto ch = str[i];
               for (char a = 'a'; a <= 'z'; a++) {
                  str[i] = a;
                  if (wordSet.count(str) > 0)
                  {
                     if (tail.count(str)) return steps;
                     frontier.insert(str);
                  }
               }
               str[i] = ch;
            }
         }

         // head <- tail
         // tail <- frontier
         std::swap(tail, frontier);
         std::swap(head, frontier);
         // expand the smaller set of words
         if (head.size() > tail.size())
         {
            std::swap(head, tail);
         }
      }
      return 0;
   }
};

//class Solution {
//public:
//    size_t ladderLength(
//       const std::string& beginWord,
//       const std::string& endWord,
//       const std::vector<std::string>& wordList)
//    {
//       // endWord not on the list
//       auto endWordIter = std::find(wordList.begin(), wordList.end(), endWord);
//       if (endWordIter == wordList.end())
//       {
//          return 0;
//       }
//       size_t endWord_index = std::distance(wordList.begin(), endWordIter);
//
//       // no need to transform at all
//       if (endWord == beginWord)
//       {
//          return 1;
//       }
//
//       // map strings to integer to make them more memory efficient
//       auto allWords = wordList;
//       allWords.push_back(beginWord);
//       std::unordered_map<std::string, size_t> str_to_index;
//       for (size_t i = 0; i < allWords.size(); i++)
//       {
//          str_to_index[allWords[i]] = i;
//       }
//
//       auto Q = std::queue<std::pair<size_t, size_t>>{};
//       Q.push({ allWords.size() - 1, 1 });
//       // the map act also acts as the visited set
//       str_to_index.erase(beginWord);
//       while (!Q.empty())
//       {
//          auto cur = Q.front();
//          Q.pop();
//
//          if (cur.first == endWord_index)
//          {
//             return cur.second;
//          }
//
//          auto next = allWords[cur.first];
//          auto next_step = cur.second + 1;
//          for (size_t i = 0; i < next.length(); i++)
//          {
//             auto original_c = next[i];
//             for (char c = 'a'; c <= 'z'; c++)
//             {
//                next[i] = c;
//                if (str_to_index.count(next) > 0)
//                {
//                   auto next_index = str_to_index.at(next);
//                   str_to_index.erase(next);
//                   Q.push({ next_index, next_step });
//                }
//             }
//             next[i] = original_c;
//         }
//       }
//
//       return 0;
//    }
//};

TEST_CASE("example")
{
   Solution solution;
   CHECK(solution.ladderLength("hit", "cog", { "hot","dot","dog","lot","log","cog" }) == 5);
   CHECK(solution.ladderLength("hit", "cog", { "hot","dot","dog","lot","log" }) == 0);
   CHECK(solution.ladderLength("hit", "hot", { "hot","dot","dog","lot","log" }) == 2);
   CHECK(solution.ladderLength("hit", "neg", { "hot","mot","mog","nog","neg" }) == 6);
}
