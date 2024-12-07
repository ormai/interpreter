#ifndef DIVIDE_EXPRESSION_HPP
#define DIVIDE_EXPRESSION_HPP

#include <format>
#include <stdexcept>
#include <string>

#include "../Color.hpp"
#include "BinaryExpression.hpp"

namespace AST {
class DivideExpression final : public BinaryExpression {
public:
  using BinaryExpression::BinaryExpression;

  ~DivideExpression() override = default;

  double interpret(Context &context) const override {
    const double op2_val = op2->interpret(context);
    if (op2_val == 0) {
      throw std::domain_error("Division by zero");
    }
    return op1->interpret(context) / op2_val;
  }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}({} {}/ {}{}){}", Color::BLUE, op1->to_string(),
                       Color::BLUE, op2->to_string(), Color::BLUE,
                       Color::DEFAULT);
  }
};
} // namespace AST

#endif // DIVIDE_EXPRESSION_HPP
