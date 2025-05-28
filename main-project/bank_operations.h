\
#ifndef BANK_OPERATIONS_H
#define BANK_OPERATIONS_H

#include "constants.h"

struct DateTime {
    int day, month, year;
    int hours, minutes, seconds;
};

struct BankOperation {
    DateTime date_time;
    char type[MAX_STRING_SIZE];
    char account[MAX_STRING_SIZE];
    double amount;
    char purpose[MAX_STRING_SIZE];
};

#endif  