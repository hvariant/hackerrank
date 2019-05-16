#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <unordered_map>
#include <queue>

// a wild solution stolen from leetcode 24 ms sample submission:
//class Solution {
//public:
//   int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
//      unordered_set<string> dict(wordList.begin(), wordList.end()), head{ beginWord }, tail{ endWord };
//      if (dict.count(endWord) == 0) return 0;
//      int i, res = 0;
//      char ch, a;
//      while (head.size()) {
//         res++;
//         unordered_set<string> t;
//         for (string str : head) {
//            dict.erase(str);
//            for (i = 0; str[i]; i++) {
//               ch = str[i];
//               for (a = 'a'; a <= 'z'; a++) {
//                  str[i] = a;
//                  if (dict.count(str)) {
//                     if (tail.count(str)) return res + 1;
//                     t.insert(str);
//                  }
//               }
//               str[i] = ch;
//            }
//         }
//         if (t.size() < tail.size()) head.swap(t);
//         else tail.swap(t), head.swap(t);
//      }
//      return 0;
//   }
//};

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

       auto Q = std::queue<std::pair<size_t, size_t>>{};
       Q.push({ allWords.size() - 1, 1 });
       // the map act also acts as the visited set
       str_to_index.erase(beginWord);
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
                   str_to_index.erase(next);
                   Q.push({ next_index, next_step });
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
