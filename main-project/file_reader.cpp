#pragma once
#include "file_reader.h"
#include "constants.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

DateTime convert_date_time(const std::string& date_str, const std::string& time_str) {
    DateTime dt;
    char sep;
    std::istringstream date_ss(date_str), time_ss(time_str);


    date_ss >> dt.day >> sep;
    if (sep != ',' || date_ss.fail()) throw std::runtime_error("  ");

    date_ss >> dt.month >> sep;
    if (sep != ',' || date_ss.fail()) throw std::runtime_error("  ");

    date_ss >> dt.year;
    if (date_ss.fail()) throw std::runtime_error("  ");


    time_ss >> dt.hours >> sep;
    if (sep != ':' || time_ss.fail()) throw std::runtime_error("  ");

    time_ss >> dt.minutes >> sep;
    if (sep != ':' || time_ss.fail()) throw std::runtime_error("  ");

    time_ss >> dt.seconds;
    if (time_ss.fail()) throw std::runtime_error("  ");


    if (dt.month < 1 || dt.month > 12) throw std::runtime_error(" ");
    if (dt.hours < 0 || dt.hours > 23) throw std::runtime_error(" ");
    if (dt.minutes < 0 || dt.minutes > 59) throw std::runtime_error(" ");

    return dt;
}

void read_bank_data(const char* file_name, BankOperation* array[], int& size) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("   : " + std::string(file_name));
    }

    size = 0;
    std::string date_str, time_str;

    while (file >> date_str >> time_str) {
        if (size >= MAX_FILE_ROWS_COUNT) {
            throw std::runtime_error("    ");
        }

        BankOperation* op = new BankOperation();
        try {
            file >> op->type >> op->account >> op->amount;


            file.get();
            file.getline(op->purpose, MAX_STRING_SIZE);

            op->date_time = convert_date_time(date_str, time_str);
            array[size++] = op;

        }
        catch (...) {
            delete op;
            throw;
        }
    }

    if (file.bad()) {
        throw std::runtime_error("  ");
    }

    file.close();
}
