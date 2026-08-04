#define JSON_ImplicitConversions 0

#include "Core.h"

int main(int argc, char** argv) {
	auto path = argv[0];

//	tst::tfn::test();
	appfn::PathTool::initialise(path);
	appfn::PathTool::initPathHomeDirectory();
	appfn::PathTool::initPathResourcesDir();
	appfn::Logger::logStatic("\n=====================\n=====================\n=====================", "main.cpp");
	Core mc;
	mc.run();
	appfn::Logger::destroy(); // Flush all remaining logs and cleanup
	std::exit(EXIT_SUCCESS);
}
