#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <queue>

struct cell
{
    size_t i;
    size_t j;
    int h;
};

bool operator>(cell const& c1, cell const& c2)
{
    return c1.h > c2.h;
}

std::vector<cell> nextStep(cell const& c, std::vector<std::vector<int>> const& heightMap)
{
    size_t const R = heightMap.size();
    size_t const C = heightMap[0].size();

    std::vector<cell> result;
    if(c.i > 0)
    {
        result.push_back(cell{c.i-1, c.j, heightMap[c.i-1][c.j]});
    }
    if(c.j > 0)
    {
        result.push_back(cell{c.i, c.j-1, heightMap[c.i][c.j-1]});
    }
    if(c.i < R-1)
    {
        result.push_back(cell{c.i+1, c.j, heightMap[c.i+1][c.j]});
    }
    if(c.j < C-1)
    {
        result.push_back(cell{c.i, c.j+1, heightMap[c.i][c.j+1]});
    }

    return result;
}

class Solution {
public:
    int trapRainWater(std::vector<std::vector<int>> const& heightMap) {
        size_t const R = heightMap.size();
        if(R <= 2) return 0;
        size_t const C = heightMap[0].size();
        if(C <= 2) return 0;

        std::priority_queue<cell, std::vector<cell>, std::greater<cell>> Q;
        auto visited = std::vector<std::vector<bool>>(R, std::vector<bool>(C, false));
        visited[0][0] = visited[0][C-1] = visited[R-1][0] = visited[R-1][C-1] = true;
        Q.push(cell{0, 0, heightMap[0][0]});
        Q.push(cell{0, C-1, heightMap[0][C-1]});
        Q.push(cell{R-1, 0, heightMap[R-1][0]});
        Q.push(cell{R-1, C-1, heightMap[R-1][C-1]});
        for(size_t i=1;i<R-1;i++)
        {
            Q.push(cell{i, 0, heightMap[i][0]});
            Q.push(cell{i, C-1, heightMap[i][C-1]});
            visited[i][0] = visited[i][C-1] = true;
        }
        for(size_t j=1;j<C-1;j++)
        {
            Q.push(cell{0, j, heightMap[0][j]});
            Q.push(cell{R-1, j, heightMap[R-1][j]});
            visited[0][j] = visited[R-1][j] = true;
        }

        int result = 0;
        while(!Q.empty())
        {
            auto current = Q.top();
            Q.pop();

            for(auto next : nextStep(current, heightMap))
            {
                if(!visited[next.i][next.j])
                {
                    if(next.h <= current.h)
                    {
//                        std::cout << "flooding (" << next.i << ", " << next.j << ")[" << next.h << "]"
//                            << " from (" << current.i << ", " << current.j << ")[" << current.h << "]" << std::endl;
                        result += current.h - next.h; // flooding the next cell
                        next.h = current.h;
                    }

                    visited[next.i][next.j] = true;
                    Q.push(std::move(next));
                }
            }
        }

        return result;
    }
};

TEST_CASE("example 1")
{
    Solution solution;
    CHECK(solution.trapRainWater(std::vector<std::vector<int>>{
        {1,4,3,1,3,2},
        {3,2,1,3,2,4},
        {2,3,3,2,3,1}}
    ) == 4);
}
