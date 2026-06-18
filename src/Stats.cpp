#include "Stats.h"
#include <iostream>

Stats::Stats() : totalBalance_(0), successCount_(0), failedCount_(0), activeThreads_(0) {
    std::cout << "[Stats] Default constructor" << std::endl;
}

Stats::Stats(int totalBalance, int successCount, int failedCount, int activeThreads)
    : totalBalance_(totalBalance), successCount_(successCount), 
      failedCount_(failedCount), activeThreads_(activeThreads) {
    std::cout << "[Stats] Constructor" << std::endl;
}

int Stats::getTotalBalance() const {
    std::cout << "[Stats] getTotalBalance() -> " << totalBalance_ << std::endl;
    return totalBalance_;
}

int Stats::getSuccessCount() const {
    std::cout << "[Stats] getSuccessCount() -> " << successCount_ << std::endl;
    return successCount_;
}

int Stats::getFailedCount() const {
    std::cout << "[Stats] getFailedCount() -> " << failedCount_ << std::endl;
    return failedCount_;
}

int Stats::getActiveThreads() const {
    std::cout << "[Stats] getActiveThreads() -> " << activeThreads_ << std::endl;
    return activeThreads_;
}