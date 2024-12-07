#ifndef UNARY_EXPRESSION_HPP
#define UNARY_EXPRESSION_HPP

#include <memory>

#include "Expression.hpp"

namespace AST {
class UnaryExpression : public Expression {
protected:
  std::unique_ptr<Expression> op;

public:
  explicit UnaryExpression(std::unique_ptr<Expression> op)
      : op(std::move(op)) {}

  ~UnaryExpression() override = default;
};
} // namespace AST

#endif // UNARY_EXPRESSION_HPP
