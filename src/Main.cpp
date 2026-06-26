#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>

#include "Account.h"
#include "Stats.h"
#include "Logger.h"
#include "Client.cpp"

using namespace std;

int main() {
    // create bank and logger instances
    Bank bank;
    Logger logger;
    atomic<bool> stopFlag(false);  // stop flag for threads

    cout << "\nBank System Starting" << endl;

    // create 5 test accounts
    int acc1 = bank.createAccount("Alice");
    int acc2 = bank.createAccount("Bob");
    int acc3 = bank.createAccount("Charlie");
    int acc4 = bank.createAccount("Diana");
    int acc5 = bank.createAccount("Eve");

    bank.depositToAccount(acc1, 1000);
    bank.depositToAccount(acc2, 1000);
    bank.depositToAccount(acc3, 1000);
    bank.depositToAccount(acc4, 1000);
    bank.depositToAccount(acc5, 1000);

    cout << "Created accounts: " << acc1 << ", " << acc2 << ", " << acc3 << ", " << acc4 << ", " << acc5 << endl;

    // start 5 client threads
    vector<thread> clients;
    for (int i = 1; i <= 5; ++i) {
        clients.emplace_back([&bank, &logger, &stopFlag, i]() {
            ClientModule client(i, bank, logger, stopFlag);
            client.run();
        });
    }

    // interactive command loop
    string command;
    while (true) {
        cout << "\n> ";
        cin >> command;

        if (command == "quit") {
            stopFlag.store(true);  // signal threads to stop
            break;
        }
        else if (command == "stats") {
            Stats s = bank.getStats();
            cout << "Total Balance: " << s.getTotalBalance() << endl;
            cout << "Success: " << s.getSuccessTransactions() << endl;
            cout << "Failed: " << s.getFailedTransactions() << endl;
            cout << "Active: " << s.getActiveClientThreads() << endl;
        }
        else if (command == "top") {
            string input;
            cin >> input;
            
            try {
                int N = stoi(input);
                if (N <= 0) {
                    cout << "Please enter a positive number." << endl;
                    continue;
                }
                
                auto top = bank.topAccounts((size_t)N);
                if (top.empty()) {
                    cout << "No accounts found." << endl;
                } else {
                    cout << "Top " << N << " accounts:" << endl;
                    for (auto* acc : top) {
                        cout << "  " << acc->getId() << " (" << acc->getName() 
                             << "): $" << acc->getBalance() << endl;
                    }
                }
            } catch (...) {
                cout << "Invalid input. Please enter a number. Example: top 3" << endl;
            }
        }
        else if (command == "balance") {
            int id;
            cin >> id;
            double balance = bank.getBalance(id);
            if (balance < 0) {
                cout << "Account not found." << endl;
            } else {
                cout << "Balance: $" << balance << endl;
            }
        }
        else if (command == "history") {
            int id;
            cin >> id;
            auto history = bank.getHistory(id);
            if (history.empty()) {
                cout << "No history found." << endl;
            } else {
                for (const auto& record : history) {
                    cout << "  " << record << endl;
                }
            }
        }
        else if (command == "help") {
            cout << "\nAvailable commands:" << endl;
            cout << "  stats          - show statistics" << endl;
            cout << "  top N          - show top N accounts" << endl;
            cout << "  balance ID     - show account balance" << endl;
            cout << "  history ID     - show transaction history" << endl;
            cout << "  help           - show this help" << endl;
            cout << "  quit           - exit program" << endl;
        }
        else {
            cout << "Unknown command. Type 'help' for available commands." << endl;
        }
    }

    // wait for all client threads to finish
    for (auto& t : clients) {
        t.join();
    }

    cout << "Bank System Shutdown" << endl;
    cout << "Logs saved to bank.log" << endl;
}