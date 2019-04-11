#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <map>
#include <vector>
#include <set>

class Solution {
public:
   size_t leastInterval(const std::vector<char>& tasks, size_t n) {
      std::map<char, size_t> freq;
      for (auto task : tasks)
      {
         if (freq.count(task) == 0)
         {
            freq[task] = 1;
         }
         else
         {
            freq[task]++;
         }
      }

      std::vector<int> prev_index(26, -1);
      using TaskFreq = std::pair<size_t, char>;
      std::set<TaskFreq, std::greater<TaskFreq>> tasks_left;
      for (const auto& entry : freq)
      {
         tasks_left.insert({ entry.second, entry.first });
      }

      size_t cur = 0;
      while (!tasks_left.empty())
      {
         auto it = tasks_left.begin();
         for (; it != tasks_left.end(); ++it)
         {
            if (prev_index[it->second - 'A'] == -1 || prev_index[it->second - 'A'] + n < cur)
            {
               break;
            }
         }

         // can schedule at least one task
         if (it != tasks_left.end())
         {
            prev_index[it->second - 'A'] = cur;

            TaskFreq tf = *it;
            tasks_left.erase(it);
            tf.first--;
            if (tf.first > 0)
            {
               tasks_left.insert(std::move(tf));
            }
         }
         cur++;
      }

      return cur;
   }
};

TEST_CASE("example")
{
   Solution solution;
   CHECK(solution.leastInterval({ 'A','A','A','B','B','B' }, 2) == 8);
   CHECK(solution.leastInterval({ 'A','A','A','A','A','A','B','C','D','E','F','G' }, 2) == 16);
}
