#pragma once
#include <string>
#include <mutex>

// Logger class declaration
class Logger {
private:
    std::mutex logMutex;      // mutex for thread-safe console output

public:
    void log(
        const std::string& level,
        const std::string& message
    );
};