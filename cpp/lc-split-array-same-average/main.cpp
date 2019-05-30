#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <unordered_map>

class Solution {
public:
   bool splitArraySameAverage(const std::vector<int>& A)
   {
      if (A.size() <= 1) return false;

      int S = 0;
      for (auto a : A)
      {
         S += a;
      }

      //
      // after this transformation, if we find a nonempty subset of A
      // such that the sum of this subset is zero, then
      // sum_j(A_j * N - S) = 0
      // iff
      // sum_j(A_j * N) = S * L where L = count(A_j)
      // iff
      // sum_j(A_j) / L = S / N
      // 
      std::vector<int> A_left;
      std::vector<int> A_right;
      for (size_t i = 0; i < A.size()/2; i++)
      {
         A_left.push_back(A[i] * A.size() - S);
      }
      for (size_t i = A.size() / 2; i < A.size(); i++)
      {
         A_right.push_back(A[i] * A.size() - S);
      }

      // if there is a zero sum subset in A_left or A_right, we are done
      // otherwise for every sum S_L in left, try to find -S_R in right.
      // note that we must make sure that S_L and S_R don't include everything
      // in A otherwise the second set will be empty.
      std::unordered_map<int, size_t> left_sums;
      std::unordered_map<int, size_t> right_sums;

      findSubsetSums(A_left, 0, 0, left_sums);
      findSubsetSums(A_right, 0, 0, right_sums);

      // remove empty subset and whole subset
      auto remove_element = [](std::unordered_map<int, size_t>& m, int k)
      {
         if (m.count(k) > 0 && m.at(k) > 0)
         {
            m.at(k)--;
         }
         if (m.at(k) == 0)
         {
            m.erase(k);
         }
      };

      remove_element(left_sums, 0);
      int left_sum = 0;
      {
         for (auto a : A_left)
         {
            left_sum += a;
         }
         remove_element(left_sums, left_sum);
      }
      remove_element(right_sums, 0);
      int right_sum = 0;
      {
         for (auto a : A_right)
         {
            right_sum += a;
         }
         remove_element(right_sums, right_sum);
      }

      // check if one of the sets can be found in left or right
      if (left_sum == 0 || left_sums.count(0) > 0)
      {
         return true;
      }
      if (right_sum == 0 || right_sums.count(0) > 0)
      {
         return true;
      }

      // if the set is separated by left and right
      // both are proper sets
      for (auto s : left_sums)
      {
         if (right_sums.count(-s.first) > 0)
         {
            return true;
         }
      }
      // the right part is a proper set
      for (auto s : right_sums)
      {
         if (left_sum + s.first == 0)
         {
            return true;
         }
      }
      // the left part is a proper set
      for (auto s : left_sums)
      {
         if (right_sum + s.first == 0)
         {
            return true;
         }
      }

      return false;
   }

private:
   void findSubsetSums(
      const std::vector<int>& A,
      size_t i,
      int sum,
      std::unordered_map<int, size_t>& sums
   )
   {
      if (i >= A.size())
      {
         if (sums.count(sum) == 0)
         {
            sums.emplace(sum, 1);
         }
         else
         {
            sums.at(sum)++;
         }

         return;
      }

      // don't take A[i]
      findSubsetSums(A, i + 1, sum, sums);
      // take A[i]
      findSubsetSums(A, i + 1, sum + A[i], sums);
   }
};

TEST_CASE("example 1")
{
   CHECK(Solution().splitArraySameAverage({ 1,6,1 }) == false);
   CHECK(Solution().splitArraySameAverage({ 1,1,1 }) == true);
   CHECK(Solution().splitArraySameAverage({ 1,2,3 }) == true);
   CHECK(Solution().splitArraySameAverage({ 1,3 }) == false);
   CHECK(Solution().splitArraySameAverage({ 60,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 }) == false);
}
