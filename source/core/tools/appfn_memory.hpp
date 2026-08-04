#ifndef CORE_APPFN_MEMORY_H
#define CORE_APPFN_MEMORY_H

#include <iostream>

#ifdef _MAC
//#include <sys/sysctl.h>
//#include <mach/mach.h>
#elif _WIN32
#include <Windows.h>
#include <Psapi.h>
#endif
namespace appfn {
class MemoryUsageMonitor {
public:
	MemoryUsageMonitor() = default;
	~MemoryUsageMonitor() = default;

	// get curent usage RAM (on byte)
	static size_t getCurrentMemoryUsage() {
#ifdef _MAC
		mach_task_basic_LINFO LINFO;
		mach_msg_type_number_t LINFOCount = MACH_TASK_BASIC_LINFO_COUNT;

		// Получаем информацию о текущем процессе
		if (task_LINFO(mach_task_self(), MACH_TASK_BASIC_LINFO, (task_LINFO_t)&LINFO, &LINFOCount) != KERN_SUCCESS) {
			std::cerr << "LERROR::MEMORY_MONITOR::FAILED_TO_GET_MEMORY_USAGE" << std::endl;
			return -1;
		}

		return static_cast<size_t>(LINFO.resident_size); // return usage in bytes
#elif _WIN32
		PROCESS_MEMORY_COUNTERS pmc;
		if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
			return static_cast<size_t>(pmc.WorkingSetSize); // return usage in bytes
		else
			std::cerr << "LERROR::MEMORY_MONITOR::FAILED_TO_GET_MEMORY_USAGE" << std::endl;
		return -1;
#endif
		return 0;
	}

	// Форматирование информации о памяти для удобного чтения
	static std::string formatMemoryUsage(long bytes) {
		constexpr long KB = 1024;
		constexpr long MB = KB * 1024;
		constexpr long GB = MB * 1024;

		if (bytes >= GB) {
			return std::to_string(bytes / GB) + " GB";
		} else if (bytes >= MB) {
			return std::to_string(bytes / MB) + " MB";
		} else if (bytes >= KB) {
			return std::to_string(bytes / KB) + " KB";
		} else {
			return std::to_string(bytes) + " B";
		}
		return "";
	}

	// Вывести текущую информацию о памяти в консоль
	static void printMemoryUsage() {
		long memoryUsage = getCurrentMemoryUsage();
		if (memoryUsage >= 0) {
			std::cout << "Current memory usage: " << formatMemoryUsage(memoryUsage) << std::endl;
		} else {
			std::cerr << "Failed to retrieve memory usage." << std::endl;
		}
	}
};
};
#endif /* CORE_APPFN_MEMORY_H */