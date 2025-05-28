// file_operations.cpp
#include "file_operations.h"
#include <vector>
#include <cstring>

BankOperation** filter_operations(
    BankOperation* array[],
    int size,
    bool (*check)(BankOperation*),
    int& result_size)
{
    std::vector<BankOperation*> result;

    for (int i = 0; i < size; i++) {
        if (check(array[i])) {
            result.push_back(array[i]);
        }
    }

    result_size = result.size();
    BankOperation** filtered = new BankOperation * [result_size];
    std::copy(result.begin(), result.end(), filtered);

    return filtered;
}

bool is_income_operation(BankOperation* op) {
    return strcmp(op->type, "Income") == 0; 
}

bool is_november2021_operation(BankOperation* op) {
    return op->date_time.month == 11 && op->date_time.year == 2021;
}


int compare_by_date(BankOperation* a, BankOperation* b) {
    if (a->date_time.year != b->date_time.year)
        return a->date_time.year - b->date_time.year;
    if (a->date_time.month != b->date_time.month)
        return a->date_time.month - b->date_time.month;
    if (a->date_time.day != b->date_time.day)
        return a->date_time.day - b->date_time.day;
    if (a->date_time.hours != b->date_time.hours)
        return a->date_time.hours - b->date_time.hours;
    if (a->date_time.minutes != b->date_time.minutes)
        return a->date_time.minutes - b->date_time.minutes;
    return a->date_time.seconds - b->date_time.seconds;
}

int compare_by_date_desc(BankOperation* a, BankOperation* b) {
    return -compare_by_date(a, b);
}

int compare_by_amount(BankOperation* a, BankOperation* b) {
    if (a->amount < b->amount) return -1;
    return (a->amount > b->amount) ? 1 : 0;
}

int compare_by_amount_desc(BankOperation* a, BankOperation* b) {
    return -compare_by_amount(a, b);
}

\
void selection_sort(BankOperation* array[], int size, CompareFunc compare) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (compare(array[j], array[min_idx]) < 0) {
                min_idx = j;
            }
        }
        std::swap(array[i], array[min_idx]);
    }
}

void quick_sort(BankOperation* array[], int size, CompareFunc compare) {
    if (size <= 1) return;

    int pivot_index = size / 2;
    BankOperation* pivot = array[pivot_index];
    int i = 0, j = size - 1;

    while (i <= j) {
        while (compare(array[i], pivot) < 0) i++;
        while (compare(array[j], pivot) > 0) j--;

        if (i <= j) {
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    quick_sort(array, j + 1, compare);
    quick_sort(array + i, size - i, compare);
}