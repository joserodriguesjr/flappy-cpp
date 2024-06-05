#include "spdlog/spdlog.h"
#include "example/factorial.hpp"

int main(int argc, char *argv[]) {
  spdlog::info("Welcomee to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);

  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical(
      "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);

  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");

  printf("Factorial of 4 is {%d}\n", Factorial(4));

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug

  spdlog::debug("This message should be displayed always..");
#ifdef DEBUG_BUILD
  spdlog::debug("This message should be displayed if DEBUG_BUILD defined..");
  spdlog::debug("This debug message should only be displayed in debug builds.");
#endif

  // Compile time log levels
  // Note that this does not change the current log level, it will only
  // remove (depending on SPDLOG_ACTIVE_LEVEL) the call on the release code.
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");

  return 0;
}