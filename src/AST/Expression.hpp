#ifndef ARITHMETIC_EXPRESSION_HPP
#define ARITHMETIC_EXPRESSION_HPP

#include <stdexcept>
#include <string>

#include "../Context.hpp"

namespace AST {
class Expression {
public:
  Expression() = default;

  virtual ~Expression() = default;

  // Only for Identifier
  [[nodiscard]] virtual std::string get_name() const {
    throw std::runtime_error("Operation not implemented for this type.");
  }

  virtual double interpret(Context &context) const = 0;

  [[nodiscard]] virtual std::string to_string() const = 0;
};
} // namespace AST

#endif // ARITHMETIC_EXPRESSION_HPP
