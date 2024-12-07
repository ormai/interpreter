#ifndef ADD_EXPRESSION_HPP
#define ADD_EXPRESSION_HPP

#include <format>
#include <string>

#include "BinaryExpression.hpp"
#include "../Color.hpp"
#include "../Context.hpp"
#include "Expression.hpp"

namespace AST {
class AddExpression final : public BinaryExpression {
public:
  using BinaryExpression::BinaryExpression;

  ~AddExpression() override = default;

  double interpret(Context &context) const override {
    return op1->interpret(context) + op2->interpret(context);
  }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}({} {}+ {}{}){}", Color::RED, op1->to_string(),
                       Color::RED, op2->to_string(), Color::RED,
                       Color::DEFAULT);
  }
};
} // namespace AST

#endif // ADD_EXPRESSION_HPP
