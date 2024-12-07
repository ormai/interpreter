#ifndef MULTIPLY_EXPRESSION_HPP
#define MULTIPLY_EXPRESSION_HPP

#include <format>
#include <string>

#include "BinaryExpression.hpp"
#include "../Color.hpp"

namespace AST {
class MultiplyExpression final : public BinaryExpression {
public:
  using BinaryExpression::BinaryExpression;

  ~MultiplyExpression() override = default;

  double interpret(Context &context) const override {
    return op1->interpret(context) * op2->interpret(context);
  }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}({} {}* {}{}){}", Color::BLUE, op1->to_string(),
                       Color::BLUE, op2->to_string(), Color::BLUE,
                       Color::DEFAULT);
  }
};
} // namespace AST

#endif // MULTIPLY_EXPRESSION_HPP
