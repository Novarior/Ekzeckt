#ifndef CORE_APPFN_PATH_H
#define CORE_APPFN_PATH_H

#include <filesystem>
#include <iostream>
#include <sstream>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <pwd.h>
#include <unistd.h>
#elif _WIN32
#include <Windows.h>
#include <shlobj.h>
#endif

const wchar_t fdoc[] = L"\\Documents\\";
const wchar_t fResoures[] = L"\\resouces\\";

namespace appfn {
class PathTool {
private:
	static std::filesystem::path pResources;
	static std::filesystem::path pDocuments;
public:
	PathTool() {}
	~PathTool() {}

	static void initialise(const char* path);
	static void initPathHomeDirectory();
	static void initPathResourcesDir();
	static bool createAppDirectories();
	static std::filesystem::path getPathDocumentsDirectory();
	static std::filesystem::path getPathResourcesDir();
	static std::filesystem::path getPathConfigDirectory();
	static bool checkAppDirectoryesExists();
	static void testRes();
	static std::string getCurrentTime();
	static void test();
};
};
#endif /* CORE_PATH_TEST_H */