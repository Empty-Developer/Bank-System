#include "Account.h"
#include <mutex>

using namespace std;

Account::Account() : id_(0), name_(""), balance_(0.0) {}

Account::Account(int id, const string& name)
    : id_(id), name_(name), balance_(0.0) {}

Account::Account(const Account& other) {
    shared_lock<shared_mutex> lock(other.mtx_);
    id_ = other.id_;
    name_ = other.name_;
    balance_ = other.balance_;
    history_ = other.history_;
}

Account& Account::operator=(const Account& other) {
    if (this != &other) {
        unique_lock<shared_mutex> thisLock(mtx_, defer_lock);
        shared_lock<shared_mutex> otherLock(other.mtx_, defer_lock);
        lock(thisLock, otherLock);

        id_ = other.id_;
        name_ = other.name_;
        balance_ = other.balance_;
        history_ = other.history_;
    }

    return *this;
}

int Account::getId() const {
    return id_;
}

string Account::getName() const {
    return name_;
}

double Account::getBalance() const {
    shared_lock<shared_mutex> lock(mtx_);
    return balance_;
}

bool Account::withdraw(double amount) {
    unique_lock<shared_mutex> lock(mtx_);
    if (amount <= 0 || balance_ < amount) {
        return false;
    }

    balance_ -= amount;
    history_.push_back("Withdraw: -" + to_string(amount));
    return true;
}

void Account::deposit(double amount) {
    unique_lock<shared_mutex> lock(mtx_);
    if (amount <= 0) {
        return;
    }

    balance_ += amount;
    history_.push_back("Deposit: +" + to_string(amount));
}

void Account::addHistory(const string& record) {
    unique_lock<shared_mutex> lock(mtx_);
    history_.push_back(record);
}

vector<string> Account::getHistory() const {
    shared_lock<shared_mutex> lock(mtx_);
    return vector<string>(history_.begin(), history_.end());
}
