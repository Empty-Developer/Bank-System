#include "Stats.h"
#include <sstream>

// Constructor: initialize all counters with zeros
Stats::Stats() 
    : totalBalance(0.0)
    , successTransactions(0)
    , failedTransactions(0)
    , activeClientThreads(0) {
}

// Method for updating statistics (used when requesting stats)
void Stats::updateStats(double balance, int success, int failed, int activeThreads) {
    totalBalance = balance;
    successTransactions = success;
    failedTransactions = failed;
    activeClientThreads = activeThreads;
}

// Getting the total balance
double Stats::getTotalBalance() const {
    return totalBalance;
}

// Getting the number of successful transactions
long long Stats::getSuccessTransactions() const {
    return successTransactions;
}

// Getting the number of rejected transactions
long long Stats::getFailedTransactions() const {
    return failedTransactions;
}

// Getting the number of active clients
int Stats::getActiveClientThreads() const {
    return activeClientThreads;
}

// Formatted representation of statistics as a string
std::string Stats::toString() const {
    std::stringstream ss;
    ss << "=== СТАТИСТИКА БАНКА ===\n"
       << "Суммарный баланс: " << totalBalance << "\n"
       << "Успешных транзакций: " << successTransactions << "\n"
       << "Отклоненных транзакций: " << failedTransactions << "\n"
       << "Активных клиентских потоков: " << activeClientThreads;
    return ss.str();
}

// Overloading the output operator for convenience
std::ostream& operator<<(std::ostream& os, const Stats& stats) {
    os << stats.toString();
    return os;
}