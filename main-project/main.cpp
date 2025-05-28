#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

#include "bank_operations.h"
#include "file_reader.h"
#include "constants.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Laboratory work #4. GIT\n";
    cout << "Variant #7. bank_operations\n";
    cout << "Author: zuikov ivan\n";
    BankOperation* operations[MAX_FILE_ROWS_COUNT];
    int size = 0;

    try {
        read_bank_data("data.txt", operations, size);

        for (int i = 0; i < size; ++i) {
            BankOperation* op = operations[i];
            cout << "\nДата операции......: "
                << setfill('0') << setw(2) << op->date_time.day << "."
                << setw(2) << op->date_time.month << "."
                << setw(4) << op->date_time.year << " "
                << setw(2) << op->date_time.hours << ":"
                << setw(2) << op->date_time.minutes << ":"
                << setw(2) << op->date_time.seconds << "\n";

            cout << "Тип операции.......: " << op->type << "\n"
                << "Номер счёта........: " << op->account << "\n"
                << "Сумма..............: " << fixed << setprecision(2) << op->amount << " руб.\n"
                << "Назначение.........: " << op->purpose << "\n"
                << string(40, '-') << endl;
        }

        for (int i = 0; i < size; ++i) {
            delete operations[i];
        }
    }
    catch (const runtime_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
        for (int i = 0; i < size; ++i) {
            delete operations[i];
        }
        return 1;
    }
    catch (const bad_alloc& e) {
        cerr << "Ошибка выделения памяти: " << e.what() << endl;
        for (int i = 0; i < size; ++i) {
            delete operations[i];
        }
        return 1;
    }
    catch (...) {
        cerr << "Неизвестная ошибка!" << endl;
        for (int i = 0; i < size; ++i) {
            delete operations[i];
        }
        return 1;
    }

    return 0;
}