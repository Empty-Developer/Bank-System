#include <iostream>
#include <vector>
#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std;


class Bank;
class Logger;

class Bank {
  public:
    vector<int> get_account_ids();
    bool transfer(int from, int to, double amount);
};

class Logger {
  public:
    void log(const string& level, const string& message);
};

class ClientModule {
  public:
    int clientId;
    Bank& bank;
    Logger& logger;
    atomic<bool>& stopFlag;

    ClientModule(int id, Bank& b, Logger& l, atomic<bool>& stop)
        : clientId(id), bank(b), logger(l), stopFlag(stop) {}

    void run() {
        srand(clientId); // У каждого клиента свой сид в майне
        logger.log("INFORMATION", "Клиент #" + to_string(clientId) + " он уже здесь");

        while (!stopFlag) {
            vector<int> ids = bank.get_account_ids();

            // перевод (минимум 2 ака)
            if (ids.size() < 2) {
                this_thread::sleep_for(chrono::milliseconds(50));
                continue;
            }

            // выбрать случайных отправителя и получателя
            int from = ids[rand() % ids.size()];
            int to   = ids[rand() % ids.size()];
            if (from == to) continue;

            
            double amount = rand() % 500 + 1;

            bool ok = bank.transfer(from, to, amount);

            // лог
            string result = ok ? " sent " : " failed ";
            logger.log(ok ? "INFO" : "WARN",
                "Client #" + to_string(clientId) +
                result + to_string((int)amount) +
                " from " + to_string(from) +
                " to " + to_string(to));

        }

        logger.log("INFORMATION", "Клиент #" + to_string(clientId) + " он ушел");
    }
};
