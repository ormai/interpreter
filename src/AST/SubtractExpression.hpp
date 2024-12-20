#ifndef SUBTRACT_EXPRESSION_HPP
#define SUBTRACT_EXPRESSION_HPP

#include <format>
#include <string>

#include "BinaryExpression.hpp"
#include "../Color.hpp"

namespace AST {
class SubtractExpression final : public BinaryExpression {
public:
  using BinaryExpression::BinaryExpression;

  ~SubtractExpression() override = default;

  double interpret(Context &context) const override {
    return op1->interpret(context) - op2->interpret(context);
  }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}({} {}- {}{}){}", Color::GREEN, op1->to_string(),
                       Color::GREEN, op2->to_string(), Color::GREEN,
                       Color::DEFAULT);
  }
};
} // namespace AST

#endif // SUBTRACT_EXPRESSION_HPP
