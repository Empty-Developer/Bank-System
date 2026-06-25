#pragma once
#include <string>
#include <chrono>

using namespace std;

class Transaction {
private:
    int fromId_;
    int toId_;
    double amount_;
    chrono::system_clock::time_point timestamp_;
    bool completed_;

public:
    Transaction();
    Transaction(int from, int to, double amount);

    int getFromId() const;
    int getToId() const;
    double getAmount() const;
    chrono::system_clock::time_point getTimestamp() const;
    bool isCompleted() const;
    void setCompleted(bool status);
    string toString() const;
};
