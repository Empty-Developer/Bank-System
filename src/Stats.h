#pragma once

// Stats class declaration
class Stats {
public: 
    double totalBalance;      // sum of all account balances
    long long successTransactions;      // number of successful transfers
    long long failedTransactions;       // number of failed transfers
    int activeClientThreads;     // currently active client threads

    Stats();
    
    Stats(double tb, long long st, long long ft, int act);
    
    
};