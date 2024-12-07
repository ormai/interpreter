#ifndef PARSER_HPP
#define PARSER_HPP

#include <cctype>
#include <cmath>
#include <format>
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
    std::unique_ptr<AST::Expression> lhs = additive(s);

    while (true) {
      s >> std::ws;
      const char op = s.peek();
      if (op == '=') {
        s.get(); // consume '='
        s >> std::ws;
        lhs = std::make_unique<AST::AssignmentExpression>(std::move(lhs),
                                                          expression(s));
        break; // Assignment is right-associative and has the lowest precedence
      }

      if (op != '+' && op != '-') {
        break;
      }

      s.get(); // consume op
      s >> std::ws;
      lhs = additive(s);
    }
    if (s.peek() != std::char_traits<char>::eof()) {
      std::string temp, remainder;
      while (s >> temp) {
        remainder += temp + ' ';
      }
      remainder.erase(remainder.size() - 1);
      throw SyntaxError(
          std::format("Expected end of expression but found '{}'", remainder));
    }
    return lhs;
  }

  /// <expression> "+" <expression> | <expression> "-" <expression>
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

  /// <expression> "*" <expression> | <expression> "/" <expression>
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

  static std::unique_ptr<AST::Expression> exponential(std::istringstream &s) {
    // exponentiation is right-associative
    std::unique_ptr<AST::Expression> left = primary(s); // maybe Constant
    while (true) {
      s >> std::ws;
      const char op = s.peek();
      if (op == '^') {
        s.get(); // consume '^'
        left = std::make_unique<AST::ExponentialExpression>(std::move(left),
                                                            exponential(s));
      } else {
        break;
      }
    }
    return left;
  }

  static std::unique_ptr<AST::Expression> primary(std::istringstream &s) {
    s >> std::ws;
    char c = s.peek();

    if (c == '(') {
      s.get(); // consume '('
      std::unique_ptr<AST::Expression> inner = additive(s);
      s >> std::ws;
      if (s.get() != ')') {
        throw SyntaxError("')' expected");
      }
      return inner;
    }

    // unary operators
    if (c == '+' || c == '-') {
      const int op = s.get();
      std::unique_ptr<AST::Expression> exp = primary(s);
      if (op == '+') {
        return std::make_unique<AST::PlusExpression>(std::move(exp));
      }
      return std::make_unique<AST::MinusExpression>(std::move(exp));
    }

    c = s.peek();
    if (std::isdigit(c) || c == '.') {
      if (double value; s >> value) {
        return std::make_unique<AST::Constant>(value);
      }
      throw SyntaxError("Invalid number literal");
    }

    std::string identifier;
    if (s >> identifier && std::isalpha(identifier[0])) {
      return std::make_unique<AST::Identifier>(identifier);
    }

    throw SyntaxError(
        std::format("Could not parse expression '{}'", identifier));
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
