#ifndef EXPONENTIAL_EXPRESSION_HPP
#define EXPONENTIAL_EXPRESSION_HPP

#include <cmath>
#include <format>
#include <string>

#include "../Color.hpp"
#include "BinaryExpression.hpp"

namespace AST {
class ExponentialExpression final : public BinaryExpression {
public:
  using BinaryExpression::BinaryExpression;

  ~ExponentialExpression() override = default;

  double interpret(Context &context) const override {
    return std::pow(op1->interpret(context), op2->interpret(context));
  }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}({}{}^{}{}){}", Color::CYAN, op1->to_string(),
                       Color::CYAN, op2->to_string(), Color::CYAN,
                       Color::DEFAULT);
  }
};
} // namespace AST

#endif // EXPONENTIAL_EXPRESSION_HPP
