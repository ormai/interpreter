#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include <format>
#include <string>

#include "../Color.hpp"
#include "Expression.hpp"

namespace AST {
class Constant final : public Expression {
  const double value;

public:
  explicit Constant(const double value) : value(value) {}

  ~Constant() override = default;

  double interpret([[maybe_unused]] Context &) const override { return value; }

  [[nodiscard]] std::string to_string() const override {
    return std::format("{}{}{}", Color::MAGENTA, value, Color::DEFAULT);
  }
};
} // namespace AST

#endif // CONSTANT_HPP
