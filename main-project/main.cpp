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
    cout << "\n���� ��������......: "
        << setfill('0') << setw(2) << op->date_time.day << "."
        << setw(2) << op->date_time.month << "."
        << setw(4) << op->date_time.year << " "
        << setw(2) << op->date_time.hours << ":"
        << setw(2) << op->date_time.minutes << ":"
        << setw(2) << op->date_time.seconds << "\n";

    cout << "��� ��������.......: " << op->type << "\n"
        << "����� �����........: " << op->account << "\n"
        << "�����.............: " << fixed << setprecision(2) << op->amount << " ���.\n"
        << "����������........: " << op->purpose << "\n"
        << string(40, '-') << endl;
}

void printFilterMenu() {
    cout << "\n�������� ��� ����������:\n"
        << "1. �������� ��� ��������\n"
        << "2. ������ ��������� ��������\n"
        << "3. �������� �� ������ 2021\n"
        << "��� �����: ";
}

void printSortMenu() {
    cout << "\n�������� ����� ����������:\n"
        << "1. ���������� �������\n"
        << "2. ������� ����������\n"
        << "��� �����: ";
}

void printCompareMenu() {
    cout << "\n�������� �������� ����������:\n"
        << "1. �� ���� �������� (�����������)\n"
        << "2. �� ���� �������� (��������)\n"
        << "3. �� ����� (�����������)\n"
        << "4. �� ����� (��������)\n"
        << "��� �����: ";
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
        cout << "������ �����!\n";
        return;
    }

    printCompareMenu();
    if (!(cin >> compareChoice)) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "������ �����!\n";
        return;
    }

    if (sortChoice < 1 || sortChoice > 2 || compareChoice < 1 || compareChoice > 4) {
        cout << "�������� ����� ����������!\n";
        return;
    }

    sortFuncs[sortChoice - 1](ops, size, compareFuncs[compareChoice - 1]);
    cout << "\n���������� ��������� �������!\n";
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
            cout << "\n������� ����:\n"
                << "1. ���������� ��������\n"
                << "2. ���������� ��������\n"
                << "3. �����\n"
                << "��� �����: ";

            if (!(cin >> mainChoice)) {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "������ �����! ���������� �����.\n";
                continue;
            }

            switch (mainChoice) {
            case 1: {
                printFilterMenu();
                int filterChoice;
                if (!(cin >> filterChoice)) {
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << "������ �����!\n";
                    break;
                }

                BankOperation** filtered = nullptr;
                int filteredSize = 0;
                bool needCleanup = false;

                switch (filterChoice) {
                case 1:
                    filtered = operations;
                    filteredSize = size;
                    cout << "\n***** ��� �������� (" << size << ") *****\n";
                    break;
                case 2:
                    filtered = filter_operations(operations, size, is_income_operation, filteredSize);
                    needCleanup = true;
                    cout << "\n***** ��������� �������� (" << filteredSize << ") *****\n";
                    break;
                case 3:
                    filtered = filter_operations(operations, size, is_november2021_operation, filteredSize);
                    needCleanup = true;
                    cout << "\n***** �������� �� ������ 2021 (" << filteredSize << ") *****\n";
                    break;
                default:
                    cout << "�������� �����!\n";
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
                    cout << "��� ������ ��� ����������!\n";
                    break;
                }
                sortOperations(operations, size);
                cout << "\n������ 5 �������� ����� ����������:\n";
                for (int i = 0; i < min(5, size); i++) {
                    printOperation(operations[i]);
                }
                break;
            case 3:
                cout << "���������� ������...\n";
                break;
            default:
                cout << "�������� �����! ���������� �����.\n";
            }
        } while (mainChoice != 3);

        for (int i = 0; i < size; i++) {
            delete operations[i];
        }
    }
    catch (const std::runtime_error& e) {
        cerr << "������: " << e.what() << endl;
        for (int i = 0; i < size; i++) {
            delete operations[i];
        }
        return 1;
    }
    catch (const std::bad_alloc& e) {
        cerr << "������ ��������� ������: " << e.what() << endl;
        for (int i = 0; i < size; i++) {
            delete operations[i];
        }
        return 1;
    }
    catch (...) {
        cerr << "����������� ������!" << endl;
        for (int i = 0; i < size; i++) {
            delete operations[i];
        }
        return 1;
    }

    return 0;
}