#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>

/// Terminal escape sequences to change the foreground color
namespace Color {
static constexpr std::string DEFAULT = "\033[0m", RED = "\033[31m",
                             GREEN = "\033[32m", YELLOW = "\033[33m",
                             BLUE = "\033[34m", MAGENTA = "\033[035m",
                             CYAN = "\033[36m";
}

#endif
