#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

// Constructor: opens the log file if a path is specified
Logger::Logger(const string& filename) 
    : logFile_(filename.empty() ? nullptr : new ofstream(filename, ios::app)) {
    if (logFile_ && logFile_->is_open()) {
        log( "INFO", "Логгер инициализирован. Файл: " + filename );
    } else if (!filename.empty()) {
            cerr << "Ошибка: не удалось открыть файл лога: " << filename << endl;
        logFile_.reset();
    }
}

// Destructor: closes the log file
Logger::~Logger() {
    if (logFile_ && logFile_->is_open()) {
        log( "INFO", "Логгер завершает работу." );
        logFile_->close();
    }
}

// Thread-safe logging of an event
void Logger::log(const string& level, const string& message) {
    // Mutex capture to protect console and file output
    lock_guard<mutex> lock(logMutex_);
    
    // Creating a timestamp
    auto now = chrono::system_clock::now();
    auto now_time_t = chrono::system_clock::to_time_t(now);
    auto now_ms = chrono::duration_cast<chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    stringstream ss;
    ss << "[" << put_time(localtime(&now_time_t), "%Y-%m-%d %H:%M:%S")
       << "." << setfill('0') << setw(3) << now_ms.count()
       << "] [" << level << "] " << message;
    
    string logEntry = ss.str();
    
    // Output to the console
    cout << logEntry << endl;
    
    // Output to a file if the file is open
    if (logFile_ && logFile_->is_open()) {
        (*logFile_) << logEntry << endl;
        logFile_->flush();
    }
}

// Logging operations with details
void Logger::logTransaction(int fromId, int toId, double amount, bool success) {
    string status = success ? "УСПЕШНО" : "ОТКЛОНЕНО";
    stringstream ss;
    ss << "Перевод " << amount << " со счета " << fromId 
       << " на счет " << toId << " - " << status;
    log("TRANSACTION", ss.str());
}

// Logging account creation
void Logger::logAccountCreation(const string& name, int id) {
    stringstream ss;
    ss << "Создан счет ID=" << id << ", владелец: \"" << name << "\"";
    log("ACCOUNT", ss.str());
}

// Error logging
void Logger::logError(const string& errorMessage) {
    log("ERROR", errorMessage);
}