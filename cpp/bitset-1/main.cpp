#include <iostream>
using namespace std;

// https://www.hackerrank.com/challenges/bitset-1/problem
// floyd's algorithm
// https://en.wikipedia.org/wiki/Cycle_detection#Tortoise_and_hare
uint64_t solve()
{
  uint64_t P, Q;
  constexpr uint64_t M = 1ull << 31;

  uint64_t N, S;
  std::cin >> N >> S >> P >> Q;

  const auto f = [P, Q, M](uint64_t a) {
    return (P*a + Q) % M;
  };

  size_t i = 2;
  uint64_t tortoise, hare;
  tortoise = f(S);
  hare = f(f(S));
  while (tortoise != hare && i < N)
  {
    tortoise = f(tortoise);
    hare = f(f(hare));
    i += 2;
  }

  if (i >= N)
  {
    return N;
  }

  size_t mu = 0;
  tortoise = S;
  while (tortoise != hare)
  {
    tortoise = f(tortoise);
    hare = f(hare);
    mu++;
  }

  size_t lambda = 1;
  hare = f(tortoise);
  while (hare != tortoise)
  {
    hare = f(hare);
    lambda++;
  }

  return mu + lambda;
}

int main() {
  std::cout << solve() << std::endl;
  return 0;
}

