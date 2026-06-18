#pragma once

class Stats {
private:
    int totalBalance_;
    int successCount_;
    int failedCount_;
    int activeThreads_;

public:
    Stats();
    Stats(int totalBalance, int successCount, int failedCount, int activeThreads);
    
    int getTotalBalance() const;
    int getSuccessCount() const;
    int getFailedCount() const;
    int getActiveThreads() const;
};  