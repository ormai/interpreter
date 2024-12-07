#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <stdexcept>
#include <string>
#include <unordered_map>

/// The context of interpreter
class Context {
  std::unordered_map<std::string, double> variables;

public:
  /// Evaluate an identifier name
  double lookup(const std::string &name) {
    if (variables.contains(name)) {
      return variables[name];
    }
    throw std::runtime_error("Unknown variable name: " + name);
  }

  /// Assign or reassign to an identifier
  void assign(const std::string &name, const double value) {
    variables[name] = value;
  }
};

#endif // CONTEXT_HPP
