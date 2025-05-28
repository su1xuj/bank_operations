#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

#include "bank_operations.h"
#include "file_reader.h"
#include "file_operations.h"
#include "constants.h"

void printOperation(const BankOperation* op) {
    cout << "\nДата операции......: "
        << setfill('0') << setw(2) << op->date_time.day << "."
        << setw(2) << op->date_time.month << "."
        << setw(4) << op->date_time.year << " "
        << setw(2) << op->date_time.hours << ":"
        << setw(2) << op->date_time.minutes << ":"
        << setw(2) << op->date_time.seconds << "\n";

    cout << "Тип операции.......: " << op->type << "\n"
        << "Номер счёта........: " << op->account << "\n"
        << "Сумма.............: " << fixed << setprecision(2) << op->amount << " руб.\n"
        << "Назначение........: " << op->purpose << "\n"
        << string(40, '-') << endl;
}

void printFilterMenu() {
    cout << "\nВыберите тип фильтрации:\n"
        << "1. Показать все операции\n"
        << "2. Только приходные операции\n"
        << "3. Операции за ноябрь 2021\n"
        << "Ваш выбор: ";
}

void printSortMenu() {
    cout << "\nВыберите метод сортировки:\n"
        << "1. Сортировка выбором\n"
        << "2. Быстрая сортировка\n"
        << "Ваш выбор: ";
}

void printCompareMenu() {
    cout << "\nВыберите критерий сортировки:\n"
        << "1. По дате операции (возрастание)\n"
        << "2. По дате операции (убывание)\n"
        << "3. По сумме (возрастание)\n"
        << "4. По сумме (убывание)\n"
        << "Ваш выбор: ";
}

void sortOperations(BankOperation* ops[], int size) {
    void (*sortFuncs[])(BankOperation * [], int, CompareFunc) = {
        selection_sort,
        quick_sort
    };

    CompareFunc compareFuncs[] = {
        compare_by_date,
        compare_by_date_desc,
        compare_by_amount,
        compare_by_amount_desc
    };

    int sortChoice, compareChoice;

    printSortMenu();
    if (!(cin >> sortChoice)) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Ошибка ввода!\n";
        return;
    }

    printCompareMenu();
    if (!(cin >> compareChoice)) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Ошибка ввода!\n";
        return;
    }

    if (sortChoice < 1 || sortChoice > 2 || compareChoice < 1 || compareChoice > 4) {
        cout << "Неверный выбор параметров!\n";
        return;
    }

    sortFuncs[sortChoice - 1](ops, size, compareFuncs[compareChoice - 1]);
    cout << "\nСортировка выполнена успешно!\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Laboratory work #4. GIT\n";
    cout << "Variant #7. bank_operations\n";
    cout << "Author: zuikov ivan\n";
    cout << "24Pi1d\n";

    BankOperation* operations[MAX_FILE_ROWS_COUNT];
    int size = 0;

    try {
        read_bank_data("data.txt", operations, size);

        int mainChoice;
        do {
            cout << "\nГлавное меню:\n"
                << "1. Фильтрация операций\n"
                << "2. Сортировка операций\n"
                << "3. Выход\n"
                << "Ваш выбор: ";

            if (!(cin >> mainChoice)) {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "Ошибка ввода! Попробуйте снова.\n";
                continue;
            }

            switch (mainChoice) {
            case 1: {
                printFilterMenu();
                int filterChoice;
                if (!(cin >> filterChoice)) {
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << "Ошибка ввода!\n";
                    break;
                }

                BankOperation** filtered = nullptr;
                int filteredSize = 0;
                bool needCleanup = false;

                switch (filterChoice) {
                case 1:
                    filtered = operations;
                    filteredSize = size;
                    cout << "\n***** Все операции (" << size << ") *****\n";
                    break;
                case 2:
                    filtered = filter_operations(operations, size, is_income_operation, filteredSize);
                    needCleanup = true;
                    cout << "\n***** Приходные операции (" << filteredSize << ") *****\n";
                    break;
                case 3:
                    filtered = filter_operations(operations, size, is_november2021_operation, filteredSize);
                    needCleanup = true;
                    cout << "\n***** Операции за ноябрь 2021 (" << filteredSize << ") *****\n";
                    break;
                default:
                    cout << "Неверный выбор!\n";
                    continue;
                }

                for (int i = 0; i < filteredSize; i++) {
                    printOperation(filtered[i]);
                }

                if (needCleanup) {
                    delete[] filtered;
                }
                break;
            }
            case 2:
                if (size == 0) {
                    cout << "Нет данных для сортировки!\n";
                    break;
                }
                sortOperations(operations, size);
                cout << "\nПервые 5 операций после сортировки:\n";
                for (int i = 0; i < min(5, size); i++) {
                    printOperation(operations[i]);
                }
                break;
            case 3:
                cout << "Завершение работы...\n";
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
            }
        } while (mainChoice != 3);

        for (int i = 0; i < size; i++) {
            delete operations[i];
        }
    }
    catch (const std::runtime_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
        for (int i = 0; i < size; i++) {
            delete operations[i];
        }
        return 1;
    }
    catch (const std::bad_alloc& e) {
        cerr << "Ошибка выделения памяти: " << e.what() << endl;
        for (int i = 0; i < size; i++) {
            delete operations[i];
        }
        return 1;
    }
    catch (...) {
        cerr << "Неизвестная ошибка!" << endl;
        for (int i = 0; i < size; i++) {
            delete operations[i];
        }
        return 1;
    }

    return 0;
}