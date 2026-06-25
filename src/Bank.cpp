#include "Account.h"
#include "Stats.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <shared_mutex>
#include <algorithm>

using namespace std;

class Bank {
  private:
    unordered_map<int, Account> accounts;
    mutable std::shared_mutex accountsMtx;

    int successCount = 0;
    int failedCount = 0;

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

    unique_lock lock(accountsMtx);

    // searching account
    auto sender = accounts.find(from);
    auto receiver = accounts.find(to);

    // basic test
    if (sender == accounts.end() || receiver == accounts.end()){
      ++failedCount;
      return false;
    }

    if (!sender->second.withdraw(amount)){ // a little money
      ++failedCount;
      return false;
    }
    /*
      if user have money. 
      append money
    */
    receiver->second.deposit(amount); 

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
    for (size_t i = 0; i < result.size(); ++i) {
      for (size_t j = 0; j + 1 < result.size() - i; ++j) {
        if (result[j]->getBalance() < result[j + 1]->getBalance()) {
            swap(result[j], result[j + 1]);
        }
      }
    }

    if (result.size() > N){ 
      /*
        if N = 3 but have 10 acc
        we output 3 acc
      */
      result.resize(N);
    }

    return result;
  }

  Stats getStats() {
    int totalBalance = 0;

    shared_lock lock(accountsMtx);

    for (auto& [id, account] : accounts){
        totalBalance += account.getBalance(); // all money all users
    }

    return Stats(totalBalance, successCount, failedCount, 0);
  }

  double getBalance(int id) const {
    shared_lock lock(accountsMtx);
    auto it = accounts.find(id);
    if (it == accounts.end()) {
        return -1.0;
    }
    return it->second.getBalance();
  }
};