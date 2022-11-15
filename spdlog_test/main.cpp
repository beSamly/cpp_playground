#include "main.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

int main() {
  spdlog::info("Welcome to spdlog!");

  // Set the default logger to file logger
  auto file_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");
  spdlog::set_default_logger(file_logger);

  // If you want to log to both console and file, please refer to the link below
  // https://github.com/gabime/spdlog/wiki/2.-Creating-loggers#creating-loggers-with-multiple-sinks
  return 0;
}