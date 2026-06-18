#include "Logger.h"
#include <iostream>

void Logger::log(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::cout << "[" << level << "] " << message << std::endl;
}