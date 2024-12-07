#ifndef SYNTAXERROR_HPP
#define SYNTAXERROR_HPP

#include <string>

/// Syntax error encountered while parsing
class SyntaxError final : public std::exception {
  std::string message;

public:
  explicit SyntaxError(std::string message) : message(std::move(message)) {}

  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

#endif // SYNTAXERROR_HPP
