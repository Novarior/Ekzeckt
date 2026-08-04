#include "appfn_pathtool.hpp"

std::filesystem::path appfn::PathTool::pResources;
std::filesystem::path appfn::PathTool::pDocuments;

void appfn::PathTool::initialise(const char* path) {

}

void appfn::PathTool::initPathHomeDirectory() {
	std::filesystem::path p;
#ifdef __APPLE__
	//struct passwd* pw = getpwuid(getuid());
	//return pw ? pw->pw_dir : nullptr;
#elif _WIN32
	PWSTR path = NULL;
	HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalDocuments, 0, NULL, &path);

	if (SUCCEEDED(hr)) {
		p = path;
		CoTaskMemFree(path);
	} else
		std::cerr << "Failed to get user folder." << std::endl;
	pDocuments = p.generic_wstring();

#endif /* SYSTEMFUNCTIONUNIX */
#ifdef _DEBUG
	std::wcout << "initPHD():: " << pDocuments << '\n';
#endif
}

void appfn::PathTool::initPathResourcesDir() {
	std::filesystem::path p;
#ifdef __APPLE__
	CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
	if (!resourceURL) {
		std::cerr << "App canno't get acsess to resources" << std::endl;
		return "";
	}

	char resourcePath[PATH_MAX];
	if (!CFURLGetFileSystemRepresentation(resourceURL, true, reinterpret_cast<UInt8*>(resourcePath), PATH_MAX)) {
		CFRelease(resourceURL);
		std::cerr << "App Can't convert data to path" << std::endl;
		return "";
	}

	CFRelease(resourceURL);
	return resourcePath;
#elif _WIN32
#if defined(_MSC_VER)
	char path[FILENAME_MAX] = {0};
	GetModuleFileNameA(nullptr, path, FILENAME_MAX);
	p = path;
	p = p.parent_path() += fResoures;
	pResources = p.generic_wstring();
#else
	char path[FILENAME_MAX];
	ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
	pResources std::filesystem::path(std::string(path, (count > 0) ? count : 0)) / fResoures;
#endif
#endif /* SYSTEMFUNCTIONUNIX */
#ifdef _DEBUG
	std::wcout << "initPHR():: " << pResources << '\n';
#endif
}

bool appfn::PathTool::createAppDirectories() {
	// collect path to application directory as PATH
 //	std::filesystem::path p = getHomeDirectory().append(fdoc).append(_appname);
 //	return std::filesystem::create_directories(p); // create dir
	return true;
}


std::filesystem::path appfn::PathTool::getPathDocumentsDirectory() {
	return pDocuments;
}
std::filesystem::path appfn::PathTool::getPathResourcesDir() {
	return pResources;
}
std::filesystem::path appfn::PathTool::getPathConfigDirectory() {
	return pDocuments / L"/config";
}
bool appfn::PathTool::checkAppDirectoryesExists() {
	return std::filesystem::exists(getPathDocumentsDirectory()) &&
		std::filesystem::exists(getPathResourcesDir());
}

void appfn::PathTool::testRes() {
	for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{pResources})
		std::cout << dir_entry << '\n';
}

std::string appfn::PathTool::getCurrentTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}

void appfn::PathTool::test() {
	initPathResourcesDir();
	std::cout << "crt:: " << getCurrentTime() << '\n';
	std::wcout << "gDEaf:: " << (checkAppDirectoryesExists() ? L"exist" : L"Notexist") << '\n';
	std::wcout << "gCaf:: " << getPathConfigDirectory() << '\n';
	std::wcout << " \npResources:: " << pResources << '\n';
	std::wcout << "pDocuments:: " << pDocuments << '\n';
	std::cout << "\n================================\n";
	testRes();
}