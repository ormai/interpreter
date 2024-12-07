#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>

/// Terminal escape sequences to change the foreground color
namespace Color {
static constexpr std::string DEFAULT = "\033[0m", RED = "\033[91m",
                             GREEN = "\033[92m", YELLOW = "\033[93m",
                             BLUE = "\033[94m", MAGENTA = "\033[95m",
                             CYAN = "\033[96m", GREY = "\033[37m";
}

#endif
