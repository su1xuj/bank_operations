#include "pch.h"
#include "CppUnitTest.h"
#include "../main-project/bank_operations.h" // Ïóòü ê çàãîëîâî÷íîìó ôàéëó
#include "../main-project/processing.h" // Ïóòü ê çàãîëîâî÷íîìó ôàéëó ñ ôóíêöèåé process

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
    // Ôóíêöèÿ äëÿ ñîçäàíèÿ îïåðàöèè
    BankOperation* build_operation(const std::string& type, double amount)
    {
        BankOperation* operation = new BankOperation;
        strncpy_s(operation->type, type.c_str(), sizeof(operation->type) - 1);
        operation->type[sizeof(operation->type) - 1] = '\0'; // ãàðàíòèðóåì íóëü-òåðìèíàòîð
        operation->amount = amount;
        return operation;
    }

    // Ôóíêöèÿ äëÿ óäàëåíèÿ ìàññèâà îïåðàöèé
    void delete_operations(BankOperation* array[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            delete array[i];
        }
    }

    TEST_CLASS(unittestproject)
    {
    public:
        TEST_METHOD(TestIncomeOperation)
        {
            BankOperation* operations[2];
            operations[0] = build_operation("Income", 100.0);
            operations[1] = build_operation("Income", 50.0);
            Assert::AreEqual(150.0, process(operations, 2));
            delete_operations(operations, 2);
        }

        TEST_METHOD(TestMultipleOperations)
        {
            BankOperation* operations[4];
            operations[0] = build_operation("Income", 300.0);
            operations[1] = build_operation("Expense", 100.0);
            operations[2] = build_operation("Income", 200.0);
            operations[3] = build_operation("Expense", 50.0);
            Assert::AreEqual(350.0, process(operations, 4));
            delete_operations(operations, 4);
        }

        TEST_METHOD(TestNoOperations)
        {
            BankOperation** operations = nullptr; // Èñïîëüçóåì nullptr
            Assert::AreEqual(0.0, process(operations, 0));
        }

        TEST_METHOD(TestOnlyExpenseOperations)
        {
            BankOperation* operations[2];
            operations[0] = build_operation("Expense", 100.0);
            operations[1] = build_operation("Expense", 50.0);
            Assert::AreEqual(-150.0, process(operations, 2));
            delete_operations(operations, 2);
        }
        TEST_METHOD(TestOtherOperations)
        {
            BankOperation* operations[2];
            operations[0] = build_operation("Transfer", 100.0);
            operations[1] = build_operation("Transfer", 50.0);
            Assert::AreEqual(0.0, process(operations, 2));
            delete_operations(operations, 2);
        }
    };
}
