#pragma once
#include <string>
#include <vector>
#include <deque>
#include <shared_mutex>

class Account {
private:
    int id_;
    std::string name_;
    double balance_;
    mutable std::shared_mutex mtx_;
    std::deque<std::string> history_;

public:
    Account();
    Account(int id, const std::string& name);
    Account(const Account& other);
    Account& operator=(const Account& other);
    
    int getId() const;
    std::string getName() const;
    double getBalance() const;
    bool withdraw(double amount);
    void deposit(double amount);
    void addHistory(const std::string& record);
    std::vector<std::string> getHistory() const;
};