#ifndef PLUS_EXPRESSION_HPP
#define PLUS_EXPRESSION_HPP

#include <format>
#include <string>

#include "../Color.hpp"
#include "Expression.hpp"
#include "UnaryExpression.hpp"

namespace AST {
class PlusExpression final : public UnaryExpression {
public:
  using UnaryExpression::UnaryExpression;

  ~PlusExpression() override = default;

  double interpret(Context &context) const override {
    return op->interpret(context);
  }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}(+{}{}){}", Color::RED, op->to_string(), Color::RED,
                       Color::DEFAULT);
  }
};
} // namespace AST

#endif // PLUS_EXPRESSION_HPP
