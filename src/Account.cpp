#include "Account.h"
#include <iostream>
#include <algorithm>
#include <shared_mutex>

Account::Account() : id_(0), name_(""), balance_(0.0) {
    std::cout << "[Account] Default constructor" << std::endl;
}

Account::Account(int id, const std::string& name) : id_(id), name_(name), balance_(0.0) {
    std::cout << "[Account] Constructor: id=" << id << ", name=" << name << std::endl;
}

Account::Account(const Account& other) 
    : id_(other.id_), name_(other.name_), balance_(other.balance_) {
    std::cout << "[Account] Copy constructor" << std::endl;
}

Account& Account::operator=(const Account& other) {
    std::cout << "[Account] Copy assignment" << std::endl;
    if (this != &other) {
        id_ = other.id_;
        name_ = other.name_;
        balance_ = other.balance_;
    }
    return *this;
}

int Account::getId() const {
    std::cout << "[Account] getId() -> " << id_ << std::endl;
    return id_;
}

std::string Account::getName() const {
    std::cout << "[Account] getName() -> " << name_ << std::endl;
    return name_;
}

double Account::getBalance() const {
    std::cout << "[Account] getBalance() -> " << balance_ << std::endl;
    return balance_;
}

bool Account::withdraw(double amount) {
    std::cout << "[Account] withdraw(" << amount << ")" << std::endl;
    return true;
}

void Account::deposit(double amount) {
    std::cout << "[Account] deposit(" << amount << ")" << std::endl;
}

void Account::addHistory(const std::string& record) {
    std::cout << "[Account] addHistory: " << record << std::endl;
}

std::vector<std::string> Account::getHistory() const {
    std::cout << "[Account] getHistory()" << std::endl;
    return {};
}   