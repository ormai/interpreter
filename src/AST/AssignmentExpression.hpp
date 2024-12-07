#ifndef ASSIGNMENT_EXPRESSION
#define ASSIGNMENT_EXPRESSION

#include <memory>

#include "Expression.hpp"

namespace AST {
class AssignmentExpression final : public Expression {
  std::unique_ptr<Expression> identifier, value;

public:
  AssignmentExpression(std::unique_ptr<Expression> identifier,
                       std::unique_ptr<Expression> value)
      : identifier(std::move(identifier)), value(std::move(value)) {}

  ~AssignmentExpression() override = default;

  double interpret(Context &context) const override {
    const double v = value->interpret(context);
    context.assign(identifier->get_name(), v);
    return v;
  }

  [[nodiscard]] std::string to_string() const override {
    return identifier->to_string();
  }
};
} // namespace AST

#endif // ASSIGNMENT_EXPRESSION
