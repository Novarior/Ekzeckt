#define JSON_ImplicitConversions 0
#include "Core.h"

int main() {

  Logger::logStatic("\n=====================\n=====================\n=====================", "main.cpp");
  Core mc;

  mc.run();

  Logger::destroy(); // Flush all remaining logs and cleanup

  return 0;
}
