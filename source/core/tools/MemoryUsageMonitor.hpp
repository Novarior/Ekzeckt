#ifndef A6FB08A8_81E3_4EB1_9D56_49788B4E2540
#define A6FB08A8_81E3_4EB1_9D56_49788B4E2540

//#include <iostream>
//#include <mach/mach.h>
//#include <sys/sysctl.h>

class MemoryUsageMonitor {
public:
    MemoryUsageMonitor() = default;
    ~MemoryUsageMonitor() = default;

    // Получение текущего использования оперативной памяти (в байтах)
    static long getCurrentMemoryUsage()
    {
        //mach_task_basic_LINFO LINFO;
        //mach_msg_type_number_t LINFOCount = MACH_TASK_BASIC_LINFO_COUNT;

        //// Получаем информацию о текущем процессе
        //if (task_LINFO(mach_task_self(), MACH_TASK_BASIC_LINFO, (task_LINFO_t)&LINFO, &LINFOCount) != KERN_SUCCESS) {
        //    std::cerr << "LERROR::MEMORY_MONITOR::FAILED_TO_GET_MEMORY_USAGE" << std::endl;
        //    return -1;
        //}

        //return static_cast<long>(LINFO.resident_size); // Возвращаем использование памяти в байтах
        return 0;
    }

    // Форматирование информации о памяти для удобного чтения
    static std::string formatMemoryUsage(long bytes)
    {
        //constexpr long KB = 1024;
        //constexpr long MB = KB * 1024;
        //constexpr long GB = MB * 1024;

        //if (bytes >= GB) {
        //    return std::to_string(bytes / GB) + " GB";
        //} else if (bytes >= MB) {
        //    return std::to_string(bytes / MB) + " MB";
        //} else if (bytes >= KB) {
        //    return std::to_string(bytes / KB) + " KB";
        //} else {
        //    return std::to_string(bytes) + " B";
        //}
        return "";
    }

    // Вывести текущую информацию о памяти в консоль
    static void printMemoryUsage()
    {
        //long memoryUsage = getCurrentMemoryUsage();
        //if (memoryUsage >= 0) {
        //    std::cout << "Current memory usage: " << formatMemoryUsage(memoryUsage) << std::endl;
        //} else {
        //    std::cerr << "Failed to retrieve memory usage." << std::endl;
        //}
    }
};

#endif /* A6FB08A8_81E3_4EB1_9D56_49788B4E2540 */
