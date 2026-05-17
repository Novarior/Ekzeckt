#ifndef LOGGER
#define LOGGER

#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <array>

#include "../_myFiles.h"
#include "../systemFunctionUNIX.hpp"

// Типы логов
enum  logType {
	LINFO = 0,
	LWARNING = 1,
	LERROR = 2
};

class Logger {
private:
  // Singleton instance
	inline static Logger* s_Instance = nullptr;
	inline static std::mutex s_Mutex;

	std::ofstream m_OutFile;    // ofs - create ofstream object for file manipulation
	std::stringstream m_Buffer; // buffer for log entries
	std::string timestamp;      // timestamp for log file name

	std::filesystem::path m_File_Path_Name; // path
	int m_BufferCount = 0;                  // counter for entries in buffer
	static const int BUFFER_LIMIT = 10;     // flush buffer after N entries

	static const std::string& logTypeToString(logType level) {
		static const std::array<std::string, 3> logTypes = {"LINFO", "LWARNING", "LERROR"};
		return logTypes[level];
	}

	void flushBufferToFile() {
		if (m_BufferCount > 0) {
			if (!m_OutFile.is_open())
				createLogFileWithTimestamp();

			m_OutFile << m_Buffer.str();
			m_OutFile.flush();
			m_Buffer.str(""); // clear buffer
			m_Buffer.clear();
			m_BufferCount = 0;
		}
	}

	void createLogFileWithTimestamp() {
		try {
			m_OutFile.open(m_File_Path_Name, std::ios::out);
			if (!m_OutFile.is_open()) {
				throw std::runtime_error("Logger: Unable to create log file with timestamp.");
			}
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	// Private constructor for singleton
	Logger() {
		timestamp = ApplicationsFunctions::getCurrentTime();
		m_File_Path_Name = ApplicationsFunctions::getDocumentsAppFolder().append(AppFiles::f_logger).append("logs_").append(timestamp).append(".log");
		
		createLogFileWithTimestamp();
	}

	// Private copy constructor (prevent copying)
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	// Get singleton instance
	static Logger& getInstance() {
		std::lock_guard<std::mutex> lock(s_Mutex);
		if (s_Instance == nullptr) {
			s_Instance = new Logger();
		}
		return *s_Instance;
	}

	// Destroy singleton instance (cleanup)

	// method for logging messages
	void log(const std::string& message, const std::string& source, logType level = logType::LINFO) {
		std::lock_guard<std::mutex> lock(s_Mutex);
		std::string logEntry = "[" + ApplicationsFunctions::getCurrentTime() + "] " + logTypeToString(level) + "\t_src: " + source + " _msg: " + message + "\n";

		// write log entry to buffer
		m_Buffer << logEntry;
		m_BufferCount++;

		if (level == logType::LWARNING || level == logType::LERROR)
			std::cerr << logEntry;

#if __MDEBUG__ == 1
		std::cout << logEntry;
#endif /* LOGGER */

		if (m_BufferCount >= BUFFER_LIMIT)
			flushBufferToFile();
	}

	static void flush() { getInstance().flushBufferToFile(); }

public:
	static void logStatic(const std::string& message, const std::string& source, logType level = logType::LINFO) {
		getInstance().log(message, source, level);
	}

	static void destroy() {
		std::lock_guard<std::mutex> lock(s_Mutex);
		if (s_Instance != nullptr) {
			s_Instance->flushBufferToFile();
			if (s_Instance->m_OutFile.is_open()) {
				s_Instance->m_OutFile.close();
			}
			delete s_Instance;
			s_Instance = nullptr;
		}
	}
};

#endif /* LOGGER */
