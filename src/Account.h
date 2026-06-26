#pragma once
#include <string>
#include <vector>
#include <deque>
#include <shared_mutex>

using namespace std;

class Account {
private:
    int id_;
    string name_;
    double balance_;
    mutable shared_mutex mtx_;
    deque<string> history_;

public:
    Account();
    Account(int id, const string& name);
    Account(const Account& other);
    Account& operator=(const Account& other);

    int getId() const;
    string getName() const;
    double getBalance() const;
    bool withdraw(double amount);
    void deposit(double amount);
    void addHistory(const string& record);
    vector<string> getHistory() const;
    shared_mutex& getMutex() const { return mtx_; }
    double getBalanceUnsafe() const { return balance_; }
    bool withdrawUnsafe(double amount);
    void depositUnsafe(double amount);
};