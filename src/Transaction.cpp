#include "Transaction.h"
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

Transaction::Transaction()
    : fromId_(0),
      toId_(0),
      amount_(0.0),
      timestamp_(chrono::system_clock::now()),
      completed_(false) {}

Transaction::Transaction(int from, int to, double amount)
    : fromId_(from),
      toId_(to),
      amount_(amount),
      timestamp_(chrono::system_clock::now()),
      completed_(false) {}

int Transaction::getFromId() const {
    return fromId_;
}

int Transaction::getToId() const {
    return toId_;
}

double Transaction::getAmount() const {
    return amount_;
}

chrono::system_clock::time_point Transaction::getTimestamp() const {
    return timestamp_;
}

bool Transaction::isCompleted() const {
    return completed_;
}

void Transaction::setCompleted(bool status) {
    completed_ = status;
}

string Transaction::toString() const {
    time_t rawTime = chrono::system_clock::to_time_t(timestamp_);
    tm localTime{};
    localtime_s(&localTime, &rawTime);

    ostringstream stream;
    stream << "Transaction[from=" << fromId_
           << ", to=" << toId_
           << ", amount=" << fixed << setprecision(2) << amount_
           << ", completed=" << (completed_ ? "true" : "false")
           << ", timestamp=" << put_time(&localTime, "%Y-%m-%d %H:%M:%S")
           << "]";
    return stream.str();
}
