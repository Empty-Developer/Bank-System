#pragma once
#include <vector>
#include <string>

class Account;
class Stats;

class Bank {
public:
    int createAccount(const std::string& name);
    std::vector<int> getAccountIds();
    bool depositToAccount(int id, double amount);
    bool transfer(int from, int to, double amount);
    std::vector<Account*> topAccounts(size_t N);
    Stats getStats();
    double getBalance(int id) const;
};  