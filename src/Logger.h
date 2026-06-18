#pragma once
#include <string>
#include <mutex>

class Logger {
private:
    std::mutex mtx_;

public:
    void log(const std::string& level, const std::string& message);
};