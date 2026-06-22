#include "Stats.h"
#include <iostream>



// constructors
Stats::Stats() : totalBalance(0.0), successTransactions(0), failedTransactions(0), activeClientThreads(0) 
{    
}
Stats::Stats(double tb, long long st, long long ft, int act)
    : totalBalance(tb), successTransactions(st), failedTransactions(ft), activeClientThreads(act)   
{   
}

