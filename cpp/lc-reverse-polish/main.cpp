#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <stack>

class Solution {
public:
    int evalRPN(const std::vector<std::string>& tokens)
    {
        std::stack<int> S;

        for(const auto& token : tokens)
        {
            if(token == "*" || token == "/" || token == "+" || token == "-")
            {
                auto op2 = S.top();
                S.pop();
                auto& op1 = S.top();

                switch(token[0])
                {
                case '*':
                    op1 = op1 * op2;
                    break;
                case '/':
                    op1 = op1 / op2;
                    break;
                case '+':
                    op1 = op1 + op2;
                    break;
                case '-':
                    op1 = op1 - op2;
                    break;
                }
            }
            else
            {
                int n = std::stoi(token);
                S.push(n);
            }
        }

        return S.top();
    }
};

TEST_CASE("example")
{
    CHECK(Solution().evalRPN({"2", "1", "+", "3", "*"}) == 9);
    CHECK(Solution().evalRPN({"4", "13", "5", "/", "+"}) == 6);
    CHECK(Solution().evalRPN({"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}) == 22);
}
