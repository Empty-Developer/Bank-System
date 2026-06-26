#include "Stats.h"
#include <sstream>

using namespace std;

// Constructor: initialize all counters with zeros
Stats::Stats() : totalBalance(0.0), successCount(0), failedCount(0), activeClientThreads(0) {}

// Method for updating statistics (used when requesting stats)
void Stats::updateStats(double balance, int success, int failed, int activeThreads) {
    totalBalance = balance;
    successCount = success;
    failedCount = failed;
    activeClientThreads = activeThreads;
}

// Getting the total balance
double Stats::getTotalBalance() const {
    return totalBalance;
}

// Getting the number of successful transactions
long long Stats::getSuccessTransactions() const {
    return successCount;
}

// Getting the number of rejected transactions
long long Stats::getFailedTransactions() const {
    return failedCount;
}

// Getting the number of active clients
int Stats::getActiveClientThreads() const {
    return activeClientThreads;
}

// Formatted representation of statistics as a string
string Stats::toString() const {
    stringstream ss;
    ss << "BANK STATISTICS\n"
       << "Total balance: " << totalBalance << "\n"
       << "Successful transactions: " << successCount << "\n"
       << "Rejected transactions: " << failedCount << "\n"
       << "Active client streams: " << activeClientThreads;
    return ss.str();
}

// Overloading the output operator for convenience
ostream& operator<<(ostream& os, const Stats& stats) {
    os << stats.toString();
    return os;
}