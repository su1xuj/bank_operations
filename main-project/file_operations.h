
#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "bank_operations.h"

BankOperation** filter_operations(BankOperation* array[], int size,
    bool (*check)(BankOperation*), int& result_size);
bool is_income_operation(BankOperation* op);
bool is_november2021_operation(BankOperation* op);

typedef int (*CompareFunc)(BankOperation*, BankOperation*);
void selection_sort(BankOperation* array[], int size, CompareFunc compare);
void quick_sort(BankOperation* array[], int size, CompareFunc compare);

int compare_by_date(BankOperation* a, BankOperation* b);
int compare_by_date_desc(BankOperation* a, BankOperation* b);
int compare_by_amount(BankOperation* a, BankOperation* b);
int compare_by_amount_desc(BankOperation* a, BankOperation* b);

#endif