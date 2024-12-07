#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <format>
#include <string>
#include <utility>

#include "../Color.hpp"
#include "Expression.hpp"

namespace AST {
class Identifier final : public Expression {
  std::string name;

public:
  explicit Identifier(std::string name) : name(std::move(name)) {}

  ~Identifier() override = default;

  [[nodiscard]] std::string get_name() const override { return name; }

  double interpret(Context &context) const override {
    return context.lookup(name);
  }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}{}{}", Color::GREEN, name, Color::DEFAULT);
  }
};
} // namespace AST

#endif // IDENTIFIER_HPP
