#include <iostream>  // For input/output stream
#include <fstream>   // For file stream (not used in provided code but maybe used in extended versions)
#include <iomanip>   // For stream manipulators
#include <cctype>    // For character functions
#include <vector>    // For using the vector container
#include <string>    // For string data type
#include <limits>    // For limits of data types
#include <cstdlib>   // For system functions
#include <algorithm> // For algorithm functions (e.g., remove)

// Define a Transaction class to represent a bank transaction
class Transaction {
private:
    std::string type; // Type of transaction (e.g., Deposit, Withdrawal)
    int amount;       // Amount of money involved in the transaction

public:
    // Constructor that initializes a transaction with a type and amount
    Transaction(std::string t, int a) : type(t), amount(a) {}

    // Method to display the transaction details
    void display() const {
        std::cout << std::setw(10) << type << std::setw(10) << amount << std::endl;
    }
};

// Define a BankAccount class to represent a bank account
class BankAccount {
private:
    int balance;                   // Amount of money in the account
    char accountType;              // Type of account (e.g., 'C' for Current, 'S' for Savings)
    int accountNumber;             // Unique number associated with the account
    std::string accountHolderName; // Name of the account holder
    std::vector<Transaction> transactions; // List of all transactions made on the account

public:
    // Default constructor initializing balance to 0, account type to 'C', and account number to 0
    BankAccount() : balance(0), accountType('C'), accountNumber(0) {}

    // Declaration of various member functions
    int getInputAccountNumber();
    std::string getInputAccountHolderName();
    char getInputAccountType();
    int getInputBalance();
    void createAccount();
    void displayAccount() const;
    void update();
    void display() const;
    int getBalance() const;
    void deposit(int amount);
    int getAccountNumber() const;
    char getAccountType() const;
    void withdraw(int amount);
    void transferFunds(BankAccount& recipient, int amount);

    // Overload the == operator to compare two bank accounts based on their account numbers
    bool operator==(const BankAccount& other) const {
        return this->accountNumber == other.accountNumber;
    }
};

// Implementations of the declared member functions for the BankAccount class

// Function to get the account number from the user.
int BankAccount::getInputAccountNumber() {
    int num;
    while (true) {
        std::cout << "Enter Account Number: ";
        if (std::cin >> num) {
            return num;
        }
        std::cout << "Invalid input. Please enter a valid account number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
// Function to get the account holder's name from the user.
std::string BankAccount::getInputAccountHolderName() {
    std::string name;
    while (true) {
        std::cout << "Enter Name of the Account Holder: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        if (name.find_first_of("0123456789") == std::string::npos) {
            return name;
        }
        std::cout << "Invalid name. Names shouldn't contain numbers.\n";
    }
}
// Function to get the account type from the user.
char BankAccount::getInputAccountType() {
    char type;
    while (true) {
        std::cout << "Enter Account Type (C/S): ";
        if (std::cin >> type) {
            type = std::toupper(type);
            if (type == 'C' || type == 'S') {
                return type;
            }
        }
        std::cout << "Invalid account type. Please enter C for Current or S for Savings.\n";
    }
}
// Function to get the initial balance from the user.
int BankAccount::getInputBalance() {
    int bal;
    while (true) {
        std::cout << "Enter Initial Balance: ";
        if (std::cin >> bal) {
            return bal;
        }
        std::cout << "Invalid input. Please enter a valid initial balance.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Function to create a new bank account.
void BankAccount::createAccount() {
    accountNumber = getInputAccountNumber();
    accountHolderName = getInputAccountHolderName();
    accountType = getInputAccountType();
    balance = getInputBalance();
}
// Function to display account details in a tabular form.
void BankAccount::displayAccount() const {
    std::cout << std::setw(10) << accountNumber << std::setw(20) << accountHolderName << std::setw(10) << accountType << std::setw(10) << balance << std::endl;
}
// Function to update account holder's name and account type.
void BankAccount::update() {
    std::cout << "\nUpdate Account Information:\n";
    accountHolderName = getInputAccountHolderName();
    accountType = getInputAccountType();
}
// Function to display detailed account information.
void BankAccount::display() const {
    std::cout << "\nAccount Number: " << accountNumber;
    std::cout << "\nAccount Holder: " << accountHolderName;
    std::cout << "\nType of Account: " << accountType;
    std::cout << "\nBalance Amount: " << balance;
    std::cout << "\nTransactions: \n";
    for (const auto& transaction : transactions) {
        transaction.display();
    }
}
// Function to get the current balance.
int BankAccount::getBalance() const {
    return balance;
}
// Function to deposit a specified amount into the account.
void BankAccount::deposit(int amount) {
    if (amount > 0) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        std::cout << "Deposited successfully!";
    } else {
        std::cout << "Invalid amount!";
    }
}
// Function to get the account number.
int BankAccount::getAccountNumber() const {
    return accountNumber;
}
// Function to get the account type.
char BankAccount::getAccountType() const {
    return accountType;
}
// Function to withdraw a specified amount from the account.
void BankAccount::withdraw(int amount) {
    if (amount <= balance && amount > 0) {
        balance -= amount;
        transactions.emplace_back("Withdrawal", amount);
        std::cout << "Withdrawn successfully!";
    } else {
        std::cout << "Insufficient balance or invalid amount!";
    }
}
// Function to transfer funds to another account.
void BankAccount::transferFunds(BankAccount& recipient, int amount) {
    if (amount <= balance && amount > 0) {
        balance -= amount;
        recipient.deposit(amount);
        transactions.emplace_back("Transfer Out", amount);
        recipient.transactions.emplace_back("Transfer In", amount);
        std::cout << "Funds transferred successfully!";
    } else {
        std::cout << "Insufficient balance or invalid amount!";
    }
} 




// Global vector to store all bank accounts in the system
std::vector<BankAccount> accounts;
// Function to search for a bank account using its account number
BankAccount* findAccount(int accNo) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNo) {
            return &acc;
        }
    }
    return nullptr;
}
// Function to create a new account and add it to the accounts list
void writeAccount() {
    BankAccount acc;
    acc.createAccount();
    accounts.push_back(acc);
}
// Function to display details of all accounts
void displayAll() {
    std::cout << "\n\n\t\tAccount holder list\n\n";
    for (const auto& acc : accounts) {
        acc.display();
    }
}
// Function to handle deposit or withdrawal operations
void depositWithdraw(int accNo, int option) {
    auto acc = findAccount(accNo);
    if (acc == nullptr) {
        std::cout << "\n\nAccount number not found...";
        return;
    }

    int amount;
    std::cout << "\n\nEnter The amount to ";
    if (option == 1) {
        std::cout << "deposit: ";
        std::cin >> amount;
        acc->deposit(amount);
    } else {
        std::cout << "withdraw: ";
        std::cin >> amount;
        acc->withdraw(amount);
    }
}
// Function to handle transfer of money between two accounts
void transferAmount(int fromAccNo, int toAccNo, int amount) {
    auto fromAcc = findAccount(fromAccNo);
    auto toAcc = findAccount(toAccNo);

    if (fromAcc == nullptr || toAcc == nullptr) {
        std::cout << "\n\nEither or both account numbers not found...";
        return;
    }

    fromAcc->transferFunds(*toAcc, amount);
}
// Utility function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    std::system("CLS");
#else
    std:system("clear");
#endif
}
// Main program logic
int main() {
    int option;

    do {
        clearScreen();
        std::cout << "\n\n\n\tMAIN MENU";
        std::cout << "\n\n\t01. NEW ACCOUNT";
        std::cout << "\n\n\t02. DEPOSIT AMOUNT";
        std::cout << "\n\n\t03. WITHDRAW AMOUNT";
        std::cout << "\n\n\t04. BALANCE ENQUIRY";
        std::cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        std::cout << "\n\n\t06. CLOSE AN ACCOUNT";
        std::cout << "\n\n\t07. TRANSFER FUNDS";
        std::cout << "\n\n\t08. EXIT";
        std::cout << "\n\n\tSelect Your Option (1-8): ";
        std::cin >> option;

        switch (option) {
        case 1:
            writeAccount();
            break;
        case 2:
            {
                int accNo;
                std::cout << "\n\n\tEnter Account Number: ";
                std::cin >> accNo;
                depositWithdraw(accNo, 1);
            }
            break;
        case 3:
            {
                int accNo;
                std::cout << "\n\n\tEnter Account Number: ";
                std::cin >> accNo;
                depositWithdraw(accNo, 2);
            }
            break;
        case 4:
            {
                int accNo;
                std::cout << "\n\n\tEnter Account Number: ";
                std::cin >> accNo;
                auto acc = findAccount(accNo);
                if (acc != nullptr) {
                    std::cout << "\n\n\tBalance: " << acc->getBalance() << std::endl;
                } else {
                    std::cout << "\n\n\tAccount number not found...";
                }
            }
            break;
        case 5:
            displayAll();
            break;
        case 6:
            {
        int accNo;
        std::cout << "\n\n\tEnter Account Number to close: ";
        std::cin >> accNo;
        
        auto acc = findAccount(accNo);
        if (acc != nullptr) {
            // Remove the account from the accounts vector
            accounts.erase(std::remove(accounts.begin(), accounts.end(), *acc), accounts.end());
            std::cout << "\n\n\tAccount closed successfully!";
        } else {
            std::cout << "\n\n\tAccount number not found...";
        }
    }
    break;
        case 7:
            {
                int fromAccNo, toAccNo, amount;
                std::cout << "\n\n\tEnter Source Account Number: ";
                std::cin >> fromAccNo;
                std::cout << "\n\n\tEnter Target Account Number: ";
                std::cin >> toAccNo;
                std::cout << "\n\n\tEnter Amount to Transfer: ";
                std::cin >> amount;
                transferAmount(fromAccNo, toAccNo, amount);
            }
            break;
        case 8:
            std::cout << "\n\n\tThanks for using our banking system!";
            break;
        default:
            std::cout << "\n\n\tInvalid choice!";
        }
        std::cin.ignore();
        std::cout << "\n\n\tPress Enter to continue...";
        std::cin.get();
    } while (option != 8);

    return 0;
}
