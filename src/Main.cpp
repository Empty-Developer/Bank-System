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

    // wait for all client threads to finish
    for (auto& t : clients) {
        t.join();
    }

    cout << "Bank System Shutdown" << endl;
    
    cout << "\nPress Enter to exit...";
    cin.get();
}