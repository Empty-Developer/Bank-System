#pragma once
#include <vector>
#include <string>

class Account;
class Stats;

class Bank {
public:
    int createAccount(const std::string& name);
    std::vector<int> getAccountIds();
    bool transfer(int from, int to, double amount);
    std::vector<Account*> topAccounts(size_t N);
    Stats getStats();
};  