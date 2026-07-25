#define JSON_ImplicitConversions 0

#include "Core.h"

int main() {
//	tst::tfn::test();
	AppFn::initPathHomeDirectory();
	AppFn::initPathResourcesDir();
	Logger::logStatic("\n=====================\n=====================\n=====================", "main.cpp");
	Core mc;
	mc.run();
	Logger::destroy(); // Flush all remaining logs and cleanup
	std::exit(EXIT_SUCCESS);
}
