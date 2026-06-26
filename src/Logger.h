#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <memory>
#include <fstream>

/**
 * Thread-safe logger for logging events to the console and file
 * Complies with requirements: one mutex to protect logging
 */
class Logger {
private:
    mutable std::mutex logMutex_;           // Output Protection
    std::unique_ptr<std::ofstream> logFile_; // Log file (optional)

public:
    explicit Logger(const std::string& filename = "bank.log");
    ~Logger();

    // The main logging method
    void log(const std::string& level, const std::string& message);
    
   // Specialized methods for convenience
    void logTransaction(int fromId, int toId, double amount, bool success);
    void logAccountCreation(const std::string& name, int id);
    void logError(const std::string& errorMessage);
};

#endif