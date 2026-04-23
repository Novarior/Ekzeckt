#ifndef SYSTEMFUNCTIONUNIX
#define SYSTEMFUNCTIONUNIX

#include "_myConst.h"
#include "_myFiles.h"

#include <filesystem>
#include <iostream>
#include <sstream>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <pwd.h>
#include <unistd.h>
#endif //__APPLE__

class ApplicationsFunctions {
private:
  /// @brief Получение пути к домашней директории
  /// @return Путь к домашней директории или `nullptr`, если не удалось
  static const char *getHomeDirectory() {
#ifdef __APPLE__
    struct passwd *pw = getpwuid(getuid());
    return pw ? pw->pw_dir : nullptr;
#else
    // Для других платформ можно использовать getenv("HOME")
    return std::getenv("HOME");
#endif /* SYSTEMFUNCTIONUNIX */
  }

public:
  ApplicationsFunctions() = default;
  ~ApplicationsFunctions() = default;

  /// @brief Создание директорий приложения в папке "Документы"
  static void createAppDirectories() {
    // collect path to application directory as string
    std::string appDirectory =
        std::string(getHomeDirectory()) + "/Documents/" + myConst::app_name;

    // create dir
    std::filesystem::create_directories(appDirectory);
    std::filesystem::create_directories(appDirectory + "/config");
  }

  /// @brief Получение пути к ресурсам приложения (только macOS)
  /// @return Путь к папке ресурсов
  static std::string get_resources_dir() {
#ifdef __APPLE__
    CFURLRef resourceURL =
        CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    if (!resourceURL) {
      std::cerr << "Не удалось получить путь к ресурсам." << std::endl;
      return "";
    }

    char resourcePath[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(
            resourceURL, true, reinterpret_cast<UInt8 *>(resourcePath),
            PATH_MAX)) {
      CFRelease(resourceURL);
      std::cerr << "Не удалось преобразовать путь к ресурсам." << std::endl;
      return "";
    }

    CFRelease(resourceURL);
    return resourcePath;
#else
    return ""; // Реализация для других платформ
#endif /* SYSTEMFUNCTIONUNIX */
  }

  /// @brief Получение пути к директории приложения в "Документах"
  /// @ /Users/$user/Documents/
  /// @return Путь к папке приложения
  static std::string getDocumentsAppFolder() {
    return std::string(getHomeDirectory()) + "/Documents/" + myConst::app_name;
  }

  /// @brief Получение пути к директории приложения в "Документах"
  /// @return Путь к папке приложения
  static std::string getAppConfigFolder() {
    return std::string(getDocumentsAppFolder()) + "/config";
  }

  /// @brief checking for exists app folder
  /// @return `true`, if directories exist, else create them
  static bool checkAppDirectoryExists() {
    return std::filesystem::exists(getDocumentsAppFolder()) ? true : false;
  }

  /// @brief Получение текущего времени в формате "YYYY-MM-DD HH:MM:SS"
  /// @return Строка с текущим временем
  static std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
  }
};

#endif /* SYSTEMFUNCTIONUNIX */
