#ifndef LOGGER
#define LOGGER

#include "../_myFiles.h"
#include "../systemFunctionUNIX.hpp"
#include <fstream>

// Типы логов
enum class logType { INFO = 0, WARNING = 1, ERROR = 2 };

class Logger {
private:
  std::ofstream mOutFile;
  std::stringstream mBuffer;
  std::filesystem::path mFilePathName =
      ApplicationsFunctions::getDocumentsAppFolder() + AppFiles::f_logger;
  std::filesystem::path backupPath =
      ApplicationsFunctions::getDocumentsAppFolder() + AppFiles::f_backup;

  // Получение строки для типа лога
  static const std::string &logTypeToString(logType level) {
    static const std::array<std::string, 3> logTypes = {"INFO", "WARNING",
                                                        "ERROR"};
    return logTypes[static_cast<int>(level)];
  }

  // file and buffer manipulation
  void openmOutFile() {
    // get path to docs/AppDocs/log.log

    // open file
    mOutFile.open(mFilePathName, std::ios::app | std::ios::out);

    if (!mOutFile) {
      std::cerr << "Logger: Unable to open the log file. Creating a new one."
                << std::endl;
      mOutFile.open(mFilePathName, std::ios::app);

      try {
        if (!mOutFile.is_open())

          throw std::runtime_error(
              "Logger: Unable to open both the main and backup log files.\n");
      }

      catch (std::exception &e) {
        std::cout << e.what();
      }
    }
  }

  // Создание резервной копии лог-файла
  void backupmOutFile() {
    try {
      if (std::filesystem::exists(mFilePathName)) {
        std::filesystem::copy(
            mFilePathName, backupPath,
            std::filesystem::copy_options::overwrite_existing);
      }
    } catch (const std::exception &e) {
      std::cerr << "Logger: Failed to create a backup of the log file: "
                << e.what() << std::endl;
    }
  }

public:
  Logger() { openmOutFile(); }

  ~Logger() {
    if (mOutFile.is_open()) {
      mOutFile.close();
      backupmOutFile();
    }
  }

  // method for logging messages
  void log(const std::string &message, const std::string &source,
           logType level = logType::INFO) {
    if (!mOutFile.is_open()) {
      openmOutFile();
    }
    // format log entry
    std::string logEntry = "[" + ApplicationsFunctions::getCurrentTime() +
                           "] " + logTypeToString(level) + "\t_src: " + source +
                           " _msg: " + message;

    mOutFile << logEntry << std::endl;

    // also output to console for WARNING and ERROR
    if (level == logType::WARNING || level == logType::ERROR) {
      std::cerr << logEntry << std::endl;
    }
#if __MDEBUG__ == 1
    // throw into console in debug mode
    std::cout << logEntry << std::endl;
#endif /* LOGGER */
  }

  // static method for easy logging without creating an instance
  // also send your logs to console in debug mode)) :D
  static void logStatic(const std::string &message, const std::string &source,
                        logType _infotype = logType::INFO) {
    try {
      Logger logger;
      logger.log(message, source, _infotype);
    } catch (const std::exception &e) {
      std::cerr << "Logger: Failed to log message: " << e.what() << std::endl;
    }
  }
};

#endif /* LOGGER */
