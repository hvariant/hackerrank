#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string_view>

class Solution {
public:
   enum class ExpressionType
   {
      number, op
   };
   struct Expression
   {
      virtual ~Expression() = default;
      virtual ExpressionType type() const = 0;
   };
   struct Number : public Expression
   {
      int n;
      ExpressionType type() const
      {
         return ExpressionType::number;
      }

      Number(int n)
         :n(n)
      {}
   };
   struct Op : public Expression
   {
      char op;
      std::unique_ptr<Expression> left, right;
      ExpressionType type() const
      {
         return ExpressionType::op;
      }

      Op(char c)
         : op(c)
      {}
   };

   int calculate(std::string_view s)
   {
      std::vector<std::string> tokens;

      {
         size_t i = 0;
         while (i < s.length())
         {
            // skip whitespace
            if (s[i] == ' ')
            {
               i++;
            }
            // a number
            else if (std::isdigit(s[i]))
            {
               std::string number;
               size_t j = i + 1;
               while (j < s.length() && std::isdigit(s[j])) j++;
               number = s.substr(i, j - i);
               tokens.emplace_back(number);

               i = j;
            }
            // assume it's an operator
            else
            {
               tokens.emplace_back(std::string(s.substr(i, 1)));
               i++;
            }
         }
      }

      {
         size_t i = 0;
         auto tree = parseSum(tokens, i);

         return fold(tree.get());
      }
   }

private:
   int fold(const Expression* root)
   {
      if (root->type() == ExpressionType::number)
      {
         return dynamic_cast<const Number*>(root)->n;
      }
      else
      {
         auto op = dynamic_cast<const Op*>(root);
         auto r_left = fold(op->left.get());
         auto r_right = fold(op->right.get());

         switch (op->op)
         {
         case '+':
            return r_left + r_right;
         case '-':
            return r_left - r_right;
         case '*':
            return r_left * r_right;
         case '/':
            return r_left / r_right;
         }

         std::string err = "unknown operator '";
         err += op->op;
         err += "'";
         throw std::runtime_error(err);
      }
   }

   //
   // CFG:
   // S -> T {[+|-] T}*
   // T -> num {[*|/] num}*
   //
   bool isTermOp(char c)
   {
      return c == '/' || c == '*';
   }
   bool isSumOp(char c)
   {
      return c == '+' || c == '-';
   }
   std::unique_ptr<Expression> parseSum(const std::vector<std::string>& tokens, size_t& i)
   {
      auto root = parseTerm(tokens, i);
      while (i < tokens.size() && isSumOp(tokens[i][0]))
      {
         auto op = parseOp(tokens, i);
         auto n2 = parseTerm(tokens, i);

         op->left = std::move(root);
         op->right = std::move(n2);
         root = std::move(op);
      }
      return root;
   }
   std::unique_ptr<Expression> parseTerm(const std::vector<std::string>& tokens, size_t& i)
   {
      std::unique_ptr<Expression> root = parseNum(tokens, i);

      while (i < tokens.size() && isTermOp(tokens[i][0]))
      {
         auto op = parseOp(tokens, i);
         auto n2 = parseNum(tokens, i);

         op->left = std::move(root);
         op->right = std::move(n2);
         root = std::move(op);
      }
      return root;
   }
   std::unique_ptr<Op> parseOp(const std::vector<std::string>& tokens, size_t& i)
   {
      return std::make_unique<Op>(tokens[i++][0]);
   }
   std::unique_ptr<Number> parseNum(const std::vector<std::string>& tokens, size_t& i)
   {
      int n = std::stoi(tokens[i++]);
      return std::make_unique<Number>(n);
   }
};

TEST_CASE("example")
{
   CHECK(Solution().calculate("3+2*2") == 7);
   CHECK(Solution().calculate(" 3/2 ") == 1);
   CHECK(Solution().calculate(" 3+5 / 2 ") == 5);
   CHECK(Solution().calculate(" 3+2*5 / 2 ") == 8);
}
