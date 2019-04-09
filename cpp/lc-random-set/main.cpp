#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <random>
#include <vector>
#include <unordered_map>

class RandomizedSet
{
public:
   /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
   bool insert(int val)
   {
      if (index_map.count(val) == 0)
      {
         elements.push_back(val);
         index_map[val] = elements.size() - 1;

         return true;
      }

      return false;
   }

   /** Removes a value from the set. Returns true if the set contained the specified element. */
   bool remove(int val)
   {
      if (index_map.count(val) != 0)
      {
         int last_element = elements.back();
         elements.pop_back();
         elements[index_map[val]] = last_element;

         index_map[last_element] = index_map[val];
         index_map.erase(val);

         return true;
      }

      return false;
   }

   /** Get a random element from the set. */
   int getRandom()
   {
      std::uniform_int_distribution<> dist(0, elements.size() - 1);
      return elements[dist(gen)];
   }

private:
   std::random_device rd;
   std::mt19937 gen{ rd() };
   std::vector<int> elements;
   std::unordered_map<int, size_t> index_map;
};
