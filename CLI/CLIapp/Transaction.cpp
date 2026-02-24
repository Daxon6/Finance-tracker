#include "Transaction.h"

bool createTransaction()
{
    // Employee Check
    json jEmployees = json::array();
    std::ifstream empFile("employees.json");
    if (empFile.is_open()) {
        try { empFile >> jEmployees; }
        catch (...) { jEmployees = json::array(); }
        empFile.close();
    }

    if (jEmployees.empty()) {
        std::cout << "No employees found. Please create employees first.\n";
        return false;
    }

    size_t choice;
    std::string input;
    Employee emp(0, "", "", "");
    while (true) {
        std::cout << "\nSelect an employee to assign:\n";
        for (size_t i = 0; i < jEmployees.size(); ++i) {
            const auto& e = jEmployees[i];
            std::cout << i + 1 << ". [" << e["id"] << "] "
                << e["firstname"].get<std::string>() << " "
                << e["lastname"].get<std::string>()
                << " (" << e["email"].get<std::string>() << ")\n";
        }

        std::cout << "Enter number: ";
        std::cin >> input;
        std::cin.ignore();

        try {
            choice = std::stoi(input);
            if (choice >= 1 && choice <= jEmployees.size()) {
                auto selected = jEmployees[choice - 1];
                emp = Employee(
                    selected["id"].get<long>(),
                    selected["firstname"].get<std::string>(),
                    selected["lastname"].get<std::string>(),
                    selected["email"].get<std::string>()
                );
                break;
            }
            std::cout << "Invalid employee selection. Try again.\n";
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid number\n";
        }
        catch (std::out_of_range&) {
            std::cout << "Number out of range\n";
        }
    }


    // Account Check
    json jAccounts = json::array();
    std::ifstream accFile("accounts.json");
    if (accFile.is_open()) {
        try {
            accFile >> jAccounts;
        }
        catch (...) {
            jAccounts = json::array();
        }
        accFile.close();
    }

    if (jAccounts.empty()) {
        std::cout << "No accounts found. Please create accounts first.\n";
        return false;
    }

    Account acc(0, AccountType::GOLD, 0.0, "", 0, Employee(0, "", "", ""));

    while (true) {
        std::cout << "\nSelect an account:\n";
        for (size_t i = 0; i < jAccounts.size(); ++i) {
            const auto& a = jAccounts[i];
            std::cout << i + 1 << ". [ID: " << a["id"] << "] "
                << "Type: " << a["type"] << ", "
                << "Balance: " << a["balance"] << " "
                << a["currency"] << "\n";
        }

        std::cout << "Enter number: ";
        std::cin >> input;
        std::cin.ignore();

        try {
            choice = std::stoi(input);
            if (choice >= 1 && choice <= jAccounts.size()) {

                auto selected = jAccounts[choice - 1];

                // Extract Employee from nested JSON
                auto empJson = selected["employee"];
                Employee empAcc(
                    empJson["id"].get<long>(),
                    empJson["firstname"].get<std::string>(),
                    empJson["lastname"].get<std::string>(),
                    empJson["email"].get<std::string>()
                );
                
                // Create Account object
                acc = Account(
                    selected["id"].get<long>(),
                    stringToAccType(selected["type"].get<std::string>()),
                    selected["balance"].get<double>(),
                    selected["currency"].get<std::string>(),
                    selected["version"].get<int>(),
                    empAcc
                );

                break;
            }

            std::cout << "Invalid account selection. Try again.\n";
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid number\n";
        }
        catch (std::out_of_range&) {
            std::cout << "Number out of range\n";
        }
    }

    // description check
    std::string description;
    std::cout << "Please provide a description" << std::endl;   
    std::regex descRegex("^[A-Za-z0-9 .,\\-_]{3,100}$");
    while (true) {
        std::cin >> description;
       
        if (std::regex_match(description, descRegex)) break;
        std::cout << "Bad description, please try again." << std::endl;
    }

    // date check

    // amount check
    long long amount;
    while (true)
    {
        std::cout << "Enter amount: ";

        if (std::cin >> amount)
        {
            if (amount < 0)
            {
                std::cout << "Amount cannot be negative.\n";
                continue;
            }

            break; // valid input
        }
        else
        {
            std::cout << "Invalid number. Please enter digits only.\n";

            std::cin.clear(); // clear fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
        }
    }

    // category check
    std::regex categoryRegex("^[A-Za-z ]+$");
    std::string category;
    while (true) {
        std::cout << "Enter category:" << std::endl;
        std::cin >> category;
        if (std::regex_match(category, categoryRegex)) break;
        std::cout << "Wrong input for category, please try again." << std::endl;
    }

    // status check
    std::string statusStr;
    int num;
    Status status;
    while (true) {
        std::cout << "\nChoose status (type number):\n";
        std::cout << " 1. COMPLETED\n 2. PENDING\n 3. RECONCILED\n";
        std::cout << "Enter number: ";
        std::cin >> statusStr;
        try {
            num = std::stoi(statusStr);
            if (num == 1) { status = Status::COMPLETED; break; }
            else if (num == 2) { status = Status::PENDING; break; }
            else if (num == 3) { status = Status::RECONCILED; break; }
            else std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid number\n";
        }
        catch (std::out_of_range&) {
            std::cout << "Number out of range\n";
        }

    }


    std::cout << "=====================================" << std::endl;
    return false;
}
