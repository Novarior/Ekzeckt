#ifndef CORE_PATH_H
#define CORE_PATH_H

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

const char _appname[] = "Ekzeckt";
const wchar_t fdoc[] = L"\\Documents\\";
const wchar_t fResoures[] = L"\\resouces\\";

class AppFn {
private:
	static std::filesystem::path pResources;
	static std::filesystem::path pDocuments;
public:
	AppFn() = default;
	~AppFn() = default;

	static void initPathHomeDirectory() {
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

	static void initPathResourcesDir() {
		std::filesystem::path p;
#ifdef __APPLE__
		CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
		if (!resourceURL) {
			std::cerr << "Не удалось получить путь к ресурсам." << std::endl;
			return "";
		}

		char resourcePath[PATH_MAX];
		if (!CFURLGetFileSystemRepresentation(resourceURL, true, reinterpret_cast<UInt8*>(resourcePath), PATH_MAX)) {
			CFRelease(resourceURL);
			std::cerr << "Не удалось преобразовать путь к ресурсам." << std::endl;
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

	static bool createAppDirectories() {
	  // collect path to application directory as PATH
	//	std::filesystem::path p = getHomeDirectory().append(fdoc).append(_appname);
	//	return std::filesystem::create_directories(p); // create dir
		return true;
	}


	static std::filesystem::path getPathDocumentsDirectory() { return pDocuments; }
	static std::filesystem::path getPathResourcesDir() { return pResources; }
	static std::filesystem::path getPathConfigDirectory() { return pDocuments / L"/config"; }
	static bool checkAppDirectoryesExists() { return std::filesystem::exists(getPathDocumentsDirectory()) && std::filesystem::exists(getPathResourcesDir()); }

	static void testRes() {
		for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{pResources})
			std::cout << dir_entry << '\n';
	}

	static std::string getCurrentTime() {
		auto now = std::chrono::system_clock::now();
		std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
		return ss.str();
	}

	static void test() {
		initPathResourcesDir();
		std::cout << "crt:: " << getCurrentTime() << '\n';
		std::wcout << "gDEaf:: " << (checkAppDirectoryesExists() ? L"exist" : L"Notexist") << '\n';
		std::wcout << "gCaf:: " << getPathConfigDirectory() << '\n';
		std::wcout << " \npResources:: " << pResources << '\n';
		std::wcout << "pDocuments:: " << pDocuments << '\n';
		std::cout << "\n================================\n";
		testRes();
	}
};


#endif /* CORE_PATH_TEST_H */