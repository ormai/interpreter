#ifndef BINARY_EXPRESSION_HPP
#define BINARY_EXPRESSION_HPP

#include <memory>

#include "Expression.hpp"

namespace AST {
class BinaryExpression : public Expression {
protected:
  std::unique_ptr<Expression> op1, op2;

public:
  BinaryExpression(std::unique_ptr<Expression> op1,
                   std::unique_ptr<Expression> op2)
      : op1(std::move(op1)), op2(std::move(op2)) {}

  ~BinaryExpression() override = default;
};
} // namespace AST

#endif // BINARY_EXPRESSION_HPP
