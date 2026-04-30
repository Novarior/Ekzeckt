#ifndef LOGGER
#define LOGGER

#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>

#include "../_myFiles.h"
#include "../systemFunctionUNIX.hpp"

// Типы логов
enum class logType { INFO = 0, WARNING = 1, ERROR = 2 };

class Logger {
private:
  // Singleton instance
  inline static Logger *s_Instance = nullptr;
  inline static std::mutex s_Mutex;

  std::ofstream m_OutFile; // ofs - create ofstream object for file manipulation
  std::stringstream m_Buffer; // buffer for log entries
  std::string timestamp;      // timestamp for log file name

  std::filesystem::path m_File_Path_Name; // path
  std::filesystem::path m_Backup_Path;    // path for backup log file
  int m_BufferCount = 0;                  // counter for entries in buffer
  static const int BUFFER_LIMIT = 10;     // flush buffer after N entries

  // get log type as string for log entry
  static const std::string &logTypeToString(logType level) {
    static const std::array<std::string, 3> logTypes = {"INFO", "WARNING",
                                                        "ERROR"};
    return logTypes[static_cast<int>(level)];
  }

  // flush buffer to file
  void flushBufferToFile() {
    if (m_BufferCount > 0) {
      if (!m_OutFile.is_open()) {
        createLogFileWithTimestamp();
      }
      m_OutFile << m_Buffer.str();
      m_OutFile.flush();
      m_Buffer.str(""); // clear buffer
      m_Buffer.clear();
      m_BufferCount = 0;
    }
  }

  // create backup of log file from current lifetime of app
  void createLogBackupFile() {
    try {
      if (std::filesystem::exists(m_File_Path_Name)) {
        std::filesystem::copy(
            m_File_Path_Name, m_Backup_Path,
            std::filesystem::copy_options::overwrite_existing);
      }
    } catch (const std::exception &e) {
      std::cerr << "Logger: Failed to create a backup of the log file: "
                << e.what() << std::endl;
    }
  }

  // create new log file with timestamp in name
  void createLogFileWithTimestamp() {
    try {
      m_OutFile.open(m_File_Path_Name, std::ios::out);
      if (!m_OutFile.is_open()) {
        throw std::runtime_error(
            "Logger: Unable to create log file with timestamp.");
      }
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  // Private constructor for singleton
  Logger() {
    timestamp = ApplicationsFunctions::getCurrentTime();
    m_File_Path_Name =
        ApplicationsFunctions::getDocumentsAppFolder() + AppFiles::f_logger;
    m_Backup_Path =
        ApplicationsFunctions::getDocumentsAppFolder() + AppFiles::f_backup;
    m_File_Path_Name = "logs_" + timestamp + ".log";
    createLogFileWithTimestamp();
  }

  // Private copy constructor (prevent copying)
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

public:
  // Get singleton instance
  static Logger &getInstance() {
    std::lock_guard<std::mutex> lock(s_Mutex);
    if (s_Instance == nullptr) {
      s_Instance = new Logger();
    }
    return *s_Instance;
  }

  // Destroy singleton instance (cleanup)
  static void destroy() {
    std::lock_guard<std::mutex> lock(s_Mutex);
    if (s_Instance != nullptr) {
      s_Instance->flushBufferToFile();
      if (s_Instance->m_OutFile.is_open()) {
        s_Instance->m_OutFile.close();
        s_Instance->createLogBackupFile();
      }
      delete s_Instance;
      s_Instance = nullptr;
    }
  }

  // method for logging messages
  void log(const std::string &message, const std::string &source,
           logType level = logType::INFO) {
    std::lock_guard<std::mutex> lock(s_Mutex);
    // create log entry with timestamp, log type, source and message
    std::string logEntry = "[" + ApplicationsFunctions::getCurrentTime() +
                           "] " + logTypeToString(level) + "\t_src: " + source +
                           " _msg: " + message + "\n";

    // write log entry to buffer
    m_Buffer << logEntry;
    m_BufferCount++;

    // also output to console for WARNING and ERROR
    if (level == logType::WARNING || level == logType::ERROR) {
      std::cerr << logEntry;
    }
#if __MDEBUG__ == 1
    // throw into console in debug mode
    std::cout << logEntry;
#endif /* LOGGER */

    // flush buffer if limit reached
    if (m_BufferCount >= BUFFER_LIMIT) {
      flushBufferToFile();
    }
  }

  // Static methods for easy logging without creating an instance
  static void logInfo(const std::string &message, const std::string &source) {
    getInstance().log(message, source, logType::INFO);
  }

  static void logWarning(const std::string &message,
                         const std::string &source) {
    getInstance().log(message, source, logType::WARNING);
  }

  static void logError(const std::string &message, const std::string &source) {
    getInstance().log(message, source, logType::ERROR);
  }

  // Static method for backward compatibility with existing code
  static void logStatic(const std::string &message, const std::string &source,
                        logType level = logType::INFO) {
    getInstance().log(message, source, level);
  }

  // flush buffer to file manually
  static void flush() { getInstance().flushBufferToFile(); }
};

#endif /* LOGGER */
