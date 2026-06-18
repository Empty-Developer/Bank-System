#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <string>

#include "Account.h"
#include "Stats.h"
#include "Logger.h"
#include "Client.cpp"

using namespace std;

int main() {
    Bank bank;
    Logger logger;
    atomic<bool> stopFlag(false);

    cout << "\nBank System Starting" << endl;

    int acc1 = bank.createAccount("Alice");
    int acc2 = bank.createAccount("Bob");
    int acc3 = bank.createAccount("Charlie");
    int acc4 = bank.createAccount("Diana");
    int acc5 = bank.createAccount("Eve");

    cout << "Created accounts: " << acc1 << ", " << acc2 << ", " << acc3 << ", " << acc4 << ", " << acc5 << endl;

    vector<thread> clients;
    for (int i = 1; i <= 5; ++i) {
        clients.emplace_back([&bank, &logger, &stopFlag, i]() {
            ClientModule client(i, bank, logger, stopFlag);
            client.run();
        });
    }

    string command;
    while (true) {
        cout << "\n> ";
        cin >> command;

        if (command == "quit") {
            stopFlag.store(true);
            break;
        }
        else if (command == "stats") {
            Stats s = bank.getStats();
            cout << "Total Balance: " << s.getTotalBalance() << endl;
            cout << "Success: " << s.getSuccessCount() << endl;
            cout << "Failed: " << s.getFailedCount() << endl;
        }
        else if (command == "top") {
            int N;
            cin >> N;
            auto top = bank.topAccounts(N);
            cout << "Top " << N << " accounts:" << endl;
            for (auto* acc : top) {
                cout << "  " << acc->getId() << " (" << acc->getName() 
                     << "): $" << acc->getBalance() << endl;
            }
        }
        else {
            cout << "Unknown command. Available: stats, top N, quit" << endl;
        }
    }

    for (auto& t : clients) {
        t.join();
    }

    cout << "Bank System Shutdown" << endl;
    
    cout << "\nPress Enter to exit...";
    cin.get();
}   