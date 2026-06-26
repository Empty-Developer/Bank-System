#ifndef STATS_H
#define STATS_H

#include <string>
#include <ostream>

/**
 * Structure for storing general bank statistics
 * Complies with requirements: totalBalance, successTransactions, 
 * failedTransactions, activeClientThreads
 */
struct Stats {
    double totalBalance;          // Total balance of all accounts
    long long successTransactions; // Number of successful transactions
    long long failedTransactions;  // Number of rejected transactions
    int activeClientThreads;       // Number of active client streams

    Stats();
    
    void updateStats(double balance, int success, int failed, int activeThreads);
    
    double getTotalBalance() const;
    long long getSuccessTransactions() const;
    long long getFailedTransactions() const;
    int getActiveClientThreads() const;
    
    std::string toString() const;
};

std::ostream& operator<<(std::ostream& os, const Stats& stats);

#endif // STATS_H