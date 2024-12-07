#include <iostream>
#include <memory>

#include "AST/Expression.hpp"
#include "Color.hpp"
#include "Context.hpp"
#include "Parser.hpp"

/// REPL
int main() {
  Context context;
  std::string line;
  while (true) {
    std::cout << "> ";
    std::getline(std::cin, line);
    if (line == "exit") {
      std::cout << "Bye!" << std::endl;
      break;
    } else if (line == "clear") {
      std::cout << "\033[H\033[2J";
      continue;
    }

    try {
      if (!line.empty()) {
        const std::unique_ptr<AST::Expression> expr = Parser::parse(line);
        std::cout << expr->to_string() << Color::GREY << " = " << Color::MAGENTA
                  << expr->interpret(context) << Color::DEFAULT << std::endl;
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }
}
