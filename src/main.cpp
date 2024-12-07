#include <iostream>
#include <memory>
#include <print>

#include "AST/Expression.hpp"
#include "Context.hpp"
#include "Parser.hpp"

/// REPL
int main() {
  Context context;
  std::string line;
  while (true) {
    std::print("> ");
    std::getline(std::cin, line);
    if (line == "exit") {
      std::println("Bye!");
      break;
    } else if (line == "clear") {
      std::println("\033[H\033[2J");
      continue;
    }

    try {
      if (!line.empty()) {
        const std::unique_ptr<AST::Expression> expr = Parser::parse(line);
        std::println("{} = {}", expr->to_string(), expr->interpret(context));
      }
    } catch (const std::exception &e) {
      std::println(stderr, "{}", e.what());
    }
  }
}
