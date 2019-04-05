#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

class Solution {
public:
   int findKthLargest(std::vector<int>& nums, int k)
   {
      quick_select(nums, 0, nums.size() - 1, k - 1);
      return nums[k - 1];
   }

private:
   size_t quick_select(std::vector<int>& list, size_t left, size_t right, size_t k)
   {
      while (left < right)
      {
         assert(left <= k);
         assert(right >= k);

         auto pivot = choose_pivot(list, left, right);
         pivot = partition(list, left, right, pivot, k);

         if (pivot == k)
         {
            return k;
         }
         else if (pivot > k)
         {
            right = pivot - 1;
         }
         else
         {
            left = pivot + 1;
         }
      }

      return left;
   }

   // 3-way partition
   size_t partition(std::vector<int>& list, size_t left, size_t right, size_t pivot, size_t k)
   {
      auto pivot_val = list[pivot];
      std::swap(list[pivot], list[right]);

      size_t bigger_index = left;
      for (size_t i = left; i < right; i++)
      {
         if (list[i] > pivot_val)
         {
            std::swap(list[i], list[bigger_index]);
            bigger_index++;
         }
      }
      // for all left <= i < bigger_index, list[i] < pivot_val

      size_t equal_index = bigger_index;
      for (size_t i = bigger_index; i < right; i++)
      {
         if (list[i] == pivot_val)
         {
            std::swap(list[i], list[equal_index]);
            equal_index++;
         }
      }
      std::swap(list[equal_index], list[right]);
      // for all bigger_index <= i <= equal_index, list[i] == pivot_val
      // for all equal_index < i <= right, list[i] > pivot_val

      if (k < bigger_index)
      {
         return bigger_index;
      }
      else if (k <= equal_index)
      {
         return k;
      }
      else
      {
         return equal_index;
      }
   }

   // divide into groups of five, calculate the medians, then put them at the start of the list
   size_t choose_pivot(std::vector<int>& list, size_t left, size_t right)
   {
      if (right < left + 5)
      {
         return partition5(list, left, right);
      }

      size_t median_index = left;
      for (size_t i = left; i <= right; i += 5)
      {
         size_t right_ = std::min(i + 4, right);
         size_t median = partition5(list, i, right_);

         std::swap(list[median_index], list[median]);
         median_index++;
      }

      size_t mid = (median_index - left) / 2 + left;
      return quick_select(list, left, median_index - 1, mid);
   }

   // bubble sort
   size_t partition5(std::vector<int>& list, size_t left, size_t right)
   {
      for (size_t i = left; i < right; i++)
      {
         for (size_t j = i; j < right; j++)
         {
            if (list[j] < list[j + 1])
            {
               std::swap(list[j], list[j + 1]);
            }
         }
      }

      return (left + right) / 2;
   }
};

TEST_CASE("example 1")
{
  Solution solution;
  std::vector<int> v = { 3,2,1,5,6,4 };
  CHECK(solution.findKthLargest(v, 1) == 6);
  CHECK(solution.findKthLargest(v, 2) == 5);
  CHECK(solution.findKthLargest(v, 3) == 4);
  CHECK(solution.findKthLargest(v, 4) == 3);
  CHECK(solution.findKthLargest(v, 5) == 2);
  CHECK(solution.findKthLargest(v, 6) == 1);
}

TEST_CASE("example 2")
{
  Solution solution;
  std::vector<int> v = { 3,2,3,1,2,4,5,5,6 };
  CHECK(solution.findKthLargest(v, 4) == 4);
}

TEST_CASE("RTE 1")
{
   Solution solution;
   auto v = std::vector<int>{ 3,2,3,1,2,4,5,5,6,7,7,8,2,3,1,1,1,10,11,5,6,2,4,7,8,5,6 };
   CHECK(solution.findKthLargest(v, 20) == 2);
}
