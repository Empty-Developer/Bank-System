#include "Account.h"
#include "Stats.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <shared_mutex>
#include <algorithm>
#include <atomic>

using namespace std;

class Bank {
  private:
    unordered_map<int, Account> accounts;
    mutable std::shared_mutex accountsMtx;

    atomic<int> successCount{0};
    atomic<int> failedCount{0};

  public:
  // methods from UML

  int createAccount(const string& name) {

    /*
      if hav 3 or more streams
      this is create a new id 
      firs call 1
      next call 2 and so on
    */ 
    static int nextId = 1; // generation id

    unique_lock lock(accountsMtx);

    int id = nextId++;

    /*
      create account while we generation id
      it append on Account(id, name)
      name get from account class
    */
    accounts.emplace(id, Account(id, name));

    return id;
  }

  vector<int> getAccountIds() {
    shared_lock lock(accountsMtx);
    vector<int> ids;
    for (const auto& [id, account] : accounts) {
      ids.push_back(id);
    }
    return ids;
  }

  bool depositToAccount(int id, double amount) {
      unique_lock lock(accountsMtx);
      auto it = accounts.find(id);
      if (it == accounts.end() || amount <= 0) {
          return false;
      }
      it->second.deposit(amount);
      return true;
  }

 bool transfer(int from, int to, double amount) {
    if (amount <= 0){
        ++failedCount;
        return false;
    }

    // searching account
    shared_lock readLock(accountsMtx);
    auto sender = accounts.find(from);
    auto receiver = accounts.find(to);

    // basic test
    if (sender == accounts.end() || receiver == accounts.end()){
      ++failedCount;
      return false;
    }

    // get references to accounts
    Account& fromAcc = sender->second;
    Account& toAcc = receiver->second;
    readLock.unlock();

    // to prevent deadlock
    int first = std::min(from, to);
    int second = std::max(from, to);

    unique_lock<shared_mutex> lock1(first == from ? fromAcc.getMutex() : toAcc.getMutex());
    unique_lock<shared_mutex> lock2(second == from ? fromAcc.getMutex() : toAcc.getMutex());

    // now safe to check and modify balances
    if (fromAcc.getBalanceUnsafe() < amount){ // a little money
      ++failedCount;
      return false;
    }
    /*
      if user have money. 
      append money
    */
    fromAcc.withdrawUnsafe(amount);
    toAcc.depositUnsafe(amount); 

    ++successCount;

    return true;
  }

  vector<Account*> topAccounts(size_t N) {
    shared_lock lock(accountsMtx);

    // collecting account links
    vector<Account*> result; 

    for (auto& [id, account] : accounts){
        result.push_back(&account);
    }

    // sort a total account 
    if (N < result.size()) {
        std::partial_sort(result.begin(), result.begin() + N, result.end(),
            [](const Account* a, const Account* b) {
                return a->getBalance() > b->getBalance();
            });
        result.resize(N);
    } else {
        std::sort(result.begin(), result.end(),
            [](const Account* a, const Account* b) {
                return a->getBalance() > b->getBalance();
            });
    }

    return result;
  }

  Stats getStats() {
    double totalBalance = 0.0;

    shared_lock lock(accountsMtx);

    for (auto& [id, account] : accounts){
        totalBalance += account.getBalance(); // all money all users
    }

    Stats stats;
    stats.updateStats(totalBalance, successCount, failedCount, 0);
    return stats;
  }

  double getBalance(int id) const {
    shared_lock lock(accountsMtx);
    auto it = accounts.find(id);
    if (it == accounts.end()) {
        return -1.0;
    }
    return it->second.getBalance();
  }

  vector<string> getHistory(int id) const {
    shared_lock lock(accountsMtx);
    auto it = accounts.find(id);
    if (it == accounts.end()) {
        return {};
    }
    return it->second.getHistory();
}
};