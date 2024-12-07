#ifndef MINUS_EXPRESSION_HPP
#define MINUS_EXPRESSION_HPP

#include <format>
#include <string>

#include "../Color.hpp"
#include "Expression.hpp"
#include "UnaryExpression.hpp"

namespace AST {
class MinusExpression final : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;

  ~MinusExpression() override = default;

  double interpret(Context &context) const override {
    return -op->interpret(context);
  }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}(-{})", Color::DEFAULT, op->to_string());
  }
};
} // namespace AST

#endif // MINUS_EXPRESSION_HPP
