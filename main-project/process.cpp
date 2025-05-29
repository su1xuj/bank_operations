#include "processing.h"

// Ôóíêöèÿ äëÿ îáðàáîòêè áàíêîâñêèõ îïåðàöèé è âû÷èñëåíèÿ òåêóùåé ñóììû íà ñ÷åòå
bool myStrEqual(const char* a, const char* b) {
    while (*a && *b) {
        if (*a != *b) return false;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

double process(BankOperation* array[], int size) {
    double total = 0.0;

    for (int i = 0; i < size; i++) {
        if (myStrEqual(array[i]->type, "Income")) {
            total += array[i]->amount;
        }
        else if (myStrEqual(array[i]->type, "Expense")) {
            total -= array[i]->amount;
        }
    }

    return total;
}
