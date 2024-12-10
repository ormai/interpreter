#ifndef PARSER_HPP
#define PARSER_HPP

#include <cctype>
#include <format>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "AST/AddExpression.hpp"
#include "AST/AssignmentExpression.hpp"
#include "AST/Constant.hpp"
#include "AST/DivideExpression.hpp"
#include "AST/ExponentialExpression.hpp"
#include "AST/Expression.hpp"
#include "AST/Identifier.hpp"
#include "AST/MinusExpression.hpp"
#include "AST/MultiplyExpression.hpp"
#include "AST/PlusExpression.hpp"
#include "AST/SubtractExpression.hpp"
#include "SyntaxError.hpp"

/// Recursive descendent parser
///
/// 1. expression
/// 2. additive
/// 3. multiplicative
/// 4. exponential
/// 5. primary
class Parser final {
  /// <expression> ::= <assignment-expression> | <additive-expression>
  static std::unique_ptr<AST::Expression> expression(std::istringstream &s) {
    // In the case of <assignment-expression> will be an <identifier>, otherwise
    // may be an <additive-expression>.
    std::unique_ptr<AST::Expression> left = additive(s); // descend

    s >> std::ws;
    const char op = s.peek();
    if (op == '=') {
      s.get(); // consume '='

      // Assignment is right-associative, so we recurse on the right side
      left = std::make_unique<AST::AssignmentExpression>(std::move(left),
                                                         expression(s));
    }

    // Everything legal has already been parsed, what's left is illegal
    if (s.peek() != std::char_traits<char>::eof()) {
      std::string leftover;
      std::getline(s, leftover);
      throw SyntaxError(
          std::format("Expected end of expression but found '{}'", leftover));
    }

    return left;
  }

  /// <additive-expression> ::= <multiplicative-expression>
  ///   | <additive-expression> "+" <multiplicative-expression>
  ///   | <additive-expression> "-" <multiplicative-expression>
  static std::unique_ptr<AST::Expression> additive(std::istringstream &s) {
    std::unique_ptr<AST::Expression> left = multiplicative(s);
    while (true) {
      s >> std::ws;
      const char op = s.peek();
      if (op == '+') {
        s.get(); // consume '+'
        left = std::make_unique<AST::AddExpression>(std::move(left),
                                                    multiplicative(s));
      } else if (op == '-') {
        s.get(); // consume '-'
        left = std::make_unique<AST::SubtractExpression>(std::move(left),
                                                         multiplicative(s));
      } else {
        return left;
      }
    }
  }

  /// <multiplicative-expression> ::= <exponential-expression>
  ///   | <multiplicative-expression> "*" <exponential-expression>
  ///   | <multiplicative-expression> "-" <exponential-expression>
  static std::unique_ptr<AST::Expression>
  multiplicative(std::istringstream &s) {
    std::unique_ptr<AST::Expression> left = exponential(s);
    while (true) {
      s >> std::ws;
      const char op = s.peek();
      if (op == '*') {
        s.get(); // consume '*'
        left = std::make_unique<AST::MultiplyExpression>(std::move(left),
                                                         exponential(s));
      } else if (op == '/') {
        s.get(); // consume '/'
        left = std::make_unique<AST::DivideExpression>(std::move(left),
                                                       exponential(s));
      } else {
        return left;
      }
    }
  }

  /// <exponential-expression> ::= <primary-expression>
  ///   | <primary-expression> "^" <exponential-expression>
  static std::unique_ptr<AST::Expression> exponential(std::istringstream &s) {
    std::unique_ptr<AST::Expression> left = primary(s);
    s >> std::ws;
    const char op = s.peek();
    if (op == '^') {
      s.get(); // consume '^'
      // right-associativity happens here, with recursion on the right op
      left = std::make_unique<AST::ExponentialExpression>(std::move(left),
                                                          exponential(s));
    }
    return left;
  }

  /// <primary-expression> ::= <number> | <identifier>
  ///   | "(" <additive-expression> ")" | <unary-expression>
  static std::unique_ptr<AST::Expression> primary(std::istringstream &s) {
    s >> std::ws;
    const char c = s.peek();

    if (c == '(') {
      s.get();
      std::unique_ptr<AST::Expression> inner = additive(s); // up again
      s >> std::ws;
      if (s.get() != ')') {
        throw SyntaxError("')' expected");
      }
      return inner;
    }

    // unary operators
    if (c == '+' || c == '-') {
      if (s.get() == '+') {
        return std::make_unique<AST::PlusExpression>(primary(s));
      }
      return std::make_unique<AST::MinusExpression>(primary(s));
    }

    if (std::isdigit(c) || c == '.') {
      if (double value; s >> value) {
        return std::make_unique<AST::Constant>(value);
      }
    }

    /// <identifier> ::= <letter> | <letter><alphanumeric-sequence>
    ///
    /// <alphanumeric-sequence> ::= <letter> | <digit> |
    ///   <letter><alphanumeric-sequence> | <digit><alphanumeric-sequence>
    if (std::isalpha(c)) {
      std::string identifier;
      identifier += s.get();
      while (std::isalnum(s.peek()) || s.peek() == '_') {
        identifier += s.get();
      }
      return std::make_unique<AST::Identifier>(identifier);
    }

    // reached the bottom of the recursive descend
    throw SyntaxError(std::format("Character not allowed '{}'", c));
  }

public:
  /// Mathematical expression parser
  ///
  /// @param expression A string representing a mathematical expression
  /// @return The abstract syntax tree representing the mathematical expression
  static std::unique_ptr<AST::Expression> parse(const std::string &input) {
    std::istringstream iss(input);
    return expression(iss);
  }
};

#endif // PARSER_HPP
