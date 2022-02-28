#include <iostream>
#include <string>
#include <vector>
#include <limits.h>
#include "bankaccount.h"
#include "bank.h"
#include "checkingaccount.h"
#include "savingsubaccount.h"


using namespace std;

int BankAccount::bankAccountAmount = 0;
int SavingAccount::savingAccountAmount = 0;
int CheckingAccount::checkingAccountAmount = 0;


// Create a list of array with each of the bank services.
 string bankService[] = {
       "A -- Number of Bank-Accounts",
       "S -- Number of Saving-Accounts",
       "H -- Number of Checking-Accounts",
       "O -- Open Bank-Account",
       "C -- Close Bank-Account",
       "M -- Modify Bank-Account",
       "D -- Detailed Bank-Accounts",
       "B -- Brief Bank-Accounts Info Sorted Based on Aggregated Balances",
       "X -- Exit"
};
 string bankAccService[] = {
       "S -- Open Saving Sub-Account",
       "C -- Open Checking Sub-Account",
       "M -- Modify a Sub-Account",
       "E -- Close a Sub-Account",
       "D -- Detailed Bank Account Info Sorted Based on Balances of Sub-Accounts",
       "B -- Brief Bank Account Info",
       "X -- Exit"
};
 string checkingAccService[] = {
       "D -- Deposit",
       "W -- Withdraw",
       "C -- Max Capacity",
       "L -- Lock Sub-Account",
       "U -- Unlock Sub-Account",
       "X -- Exit"
};
 string savingAccService[] = {
       "D -- Deposit",
       "W -- Withdraw",
       "X -- Exit"
};


//Create a list of array for the output.

 string bankInitialize[] = {
       "Enter the name of the bank: ",
       "Enter the address of the bank: ",
       "Enter the working hours: "
};
 string accountInitialize[] = {
       "\tEnter the first name of the account holder: ",
       "\tEnter the last name of the account holder: ",
       "\tEnter the SSN of the account holder: "
};
 string accModifyInitialize[] = {
       "\tEnter the bank-account number to modify: "
};
 string accCloseInitialize[] = {
       "\tEnter the bank-account number to be closed: "
};
 string subModifyInitialize[] = {
       "\tEnter the sub-account number to modify: "
};
 string subCloseInitialize[] = {
       "\tEnter the sub-account number to be closed: "
};
 string depositInitialize[] = {
       "\tEnter the amount to deposit: "
};
 string withdrawInitialize[] = {
       "\tEnter the amount to withdraw: "
};
 string capInitialize[] = {
       "\tEnter the new maximum capacity: "
};
 string savingInitialize[] = {
       "\tEnter the initial balance: "
};
 string checkingInitialize[] = {
       "\tEnter the initial balance: ",
       "\tEnter the desired maximum capacity: ",
       "\tDefine initial state: (L - locked, Otherwise - Unlocked) "
};

void printOutput(string output) {
    cout << "\t\033[;31m| " << output << "\033[0m\n";
}

void printServices(const string service, const string serviceArray[], const int size) {
    cout << "\033[;32m Eligiable services for " << service << "\033[0m\n";
    for (int i = 0; i < size; i++) {
        cout << "\t\t\033[;32m" << serviceArray[i] << "\033[0m\n";
    }
    cout << "\033[;32m Please enter your selection:\033[0m";
}

void printInput(string& userInput, string inputOutput) {
    cout <<"\033[;35m"<< inputOutput << "\033[0m";
    // I couldn't find the brown color code for Linux so I just go with the color that looks the most similar with.

    while (userInput.size() == 0)
        getline(cin, userInput);
    cin.clear();
}


void printInputArray(string userInputArray[], const int size, const string inputOutput[]) {
    for (int i = 0; i < size; i++) {
        string userInput;
        printInput(userInput, inputOutput[i]);
        userInputArray[i] = userInput;
    }
}


// Initialize saving account menu.

void initializeSavingAccount(SavingAccount* savingAcc) {
    char savingAccInput = ' ';
    while (savingAccInput != 'X' && savingAccInput != 'x') {
        printServices("sub-account SAV" + to_string(savingAcc->getBankId()), savingAccService, 3);
        cin >> savingAccInput;
        if (savingAccInput == 'D' || savingAccInput == 'd') {
            string inputArr[1];
            printInputArray(inputArr, 1, depositInitialize);
            int depositAmount;
            // exception begins
            try {
                depositAmount = stoi(inputArr[0]); 
            }
            catch (invalid_argument) {
                depositAmount = -1;
            }
            if (depositAmount > 0) {
                savingAcc->deposit(depositAmount);
                printOutput("Deposit was successful.");
                printOutput("The current balance is " + to_string(savingAcc->getBalance()));
            }
            else {
                printOutput("Deposit was unsuccessful.");
            }
            cout << endl << endl << endl;
        }
        else if (savingAccInput == 'W' || savingAccInput == 'w') {
            string inputArr[1];
            printInputArray(inputArr, 1, withdrawInitialize);
            int withdrawAmount;
            try {
                withdrawAmount = stoi(inputArr[0]);
            }
            catch (invalid_argument) {
                withdrawAmount = INT_MAX;
            }
            if (savingAcc->getBalance() - withdrawAmount >= 0) {
                savingAcc->withdraw(withdrawAmount);
                printOutput("Withdraw was successful.");
                printOutput("The current balance is " + to_string(savingAcc->getBalance()));
            }
            else {
                printOutput("Withdraw was unsuccessful.");
            }
            cout << endl << endl << endl;
        }
    }
    printOutput("End of service for sub-account SAV" + to_string(savingAcc->getBankId()));
}


// Initialize checking account menu.

void initializeCheckingAccount(CheckingAccount* checkingAcc) {
    char checkingAccInput = ' ';
    while (checkingAccInput != 'X' && checkingAccInput != 'x') {
        printServices("sub-account CHK" + to_string(checkingAcc->getBankId()), checkingAccService, 6);
        cin >> checkingAccInput;
        if (checkingAccInput == 'D' || checkingAccInput == 'd') {
            string inputArr[1];
            printInputArray(inputArr, 1, depositInitialize);
            int depositAmount;
            try {
                depositAmount = stoi(inputArr[0]);
            }
            catch (invalid_argument) {
                depositAmount = -1;
            }

            if (checkingAcc->isLocked()) {
                printOutput("The account is currently locked!");
                printOutput("The deposit was unsuccessful.");
                continue;
            }

            if (depositAmount > 0) {
                checkingAcc->deposit(depositAmount);
                printOutput("Deposit was successful.");
                printOutput("The current balance is " + to_string(checkingAcc->getBalance()));
            }
            else {
                printOutput("Deposit was unsuccessful.");
            }
            cout << endl << endl << endl;
        }
        else if (checkingAccInput == 'W' || checkingAccInput == 'w') {
            string inputArr[1];
            printInputArray(inputArr, 1, withdrawInitialize);
            int withdrawAmount;
            try {
                withdrawAmount = stoi(inputArr[0]);
            }
            catch (invalid_argument) {
                withdrawAmount = INT_MAX;
            }

            if (checkingAcc->isLocked()) {
                printOutput("The account is currently locked!");
                printOutput("The withdraw was unsuccessful.");
                continue;
            }

            if (checkingAcc->getBalance() - withdrawAmount >= 0) {
                checkingAcc->withdraw(withdrawAmount);
                printOutput("Withdraw was successful.");
                printOutput("The current balance is " + to_string(checkingAcc->getBalance()));
            }
            else {
                printOutput("Withdraw was unsuccessful.");
            }
            cout << endl << endl << endl;
        }
        else if (checkingAccInput == 'C' || checkingAccInput == 'c') {
            string inputArr[1];
            int maxCap;
            try {
                do {
                    printInputArray(inputArr, 1, capInitialize);
                    maxCap = stoi(inputArr[0]);
                } while (maxCap < 0 || maxCap < checkingAcc->getBalance());

                checkingAcc->setCap(maxCap);
                printOutput("Max capacity has been set.");
            }
            catch (invalid_argument) {
                printOutput("Error setting max capacity.");
            }
        }
        else if (checkingAccInput == 'L' || checkingAccInput == 'l') {
            checkingAcc->setLocked(true);
            printOutput("The sub-account CHK" + to_string(checkingAcc->getBankId()) + " is locked now!");
        }
        else if (checkingAccInput == 'U' || checkingAccInput == 'u') {
            checkingAcc->setLocked(false);
            printOutput("The sub-account CHK" + to_string(checkingAcc->getBankId()) + " is unlocked now!");
        }
    }
    printOutput("End of service for sub-account CHK" + to_string(checkingAcc->getBankId()));
}


// Initialize checking account menu.

void initializeBankAccount(BankAccount* bankAcc, CheckingAccount* checkingAcc, SavingAccount* savingAcc) {
    char bankAccInput = ' ';
    while (bankAccInput != 'X' && bankAccInput != 'x') {
        printServices("Bank-Account BNK" + to_string(bankAcc->getBankId()), bankAccService, 7);
        cin >> bankAccInput;
        if (bankAccInput == 'S' || bankAccInput == 's') {
            string inputArr[1];
            int initBal;
            try {
                do {
                    printInputArray(inputArr, 1, savingInitialize);
                    initBal = stoi(inputArr[0]);
                } while (initBal < 0);

                savingAcc = bankAcc->createNewSavingAccount(initBal);
                printOutput("A new Saving Sub-Account SAV" + to_string(savingAcc->getBankId()) + " was successfully created.");
                savingAcc = nullptr;
            }
            catch (invalid_argument) {
                printOutput("Error creating new Saving Sub-Account.");
            }
        }
        else if (bankAccInput == 'C' || bankAccInput == 'c') {
            string inputArr[3];
            int initBal;
            int maxCap;
            try {
                do {
                    printInputArray(inputArr, 3, checkingInitialize);
                    initBal = stoi(inputArr[0]);
                    maxCap = stoi(inputArr[1]);
                } while (initBal < 0 || maxCap < 0 || initBal > maxCap);

                bool locked = false;
                if (inputArr[2] == "L" || inputArr[2] == "l")
                    locked = true;
                checkingAcc = bankAcc->createNewCheckingAccount(initBal, maxCap, locked);
                printOutput("A new Checking Sub-Account CHK" + to_string(checkingAcc->getBankId()) +
                    " was successfully created.");
                checkingAcc = nullptr;
            }
            catch (invalid_argument) {
                printOutput("Error creating new Checking Sub-Account");
            }
        }
        else if (bankAccInput == 'M' || bankAccInput == 'm') {
            string inputArr[1];
            printInputArray(inputArr, 1, subModifyInitialize);

            string accType;
            int AccountNum;

            if (inputArr[0].length() >= 7) {
                accType = inputArr->substr(0, 3);
                try {
                    AccountNum = stoi(inputArr->substr(3, 4));
                }
                catch (invalid_argument) { /* do nothing */ }
            }

            bool foundAccount = false;

            if (accType == "SAV") {
                foundAccount = bankAcc->getSavingAccount(AccountNum, savingAcc);
                if (foundAccount)
                    initializeSavingAccount(savingAcc);
            }
            else if (accType == "CHK") {
                foundAccount = bankAcc->getCheckingAccount(AccountNum, checkingAcc);
                if (foundAccount)
                    initializeCheckingAccount(checkingAcc);
            }
            if (!foundAccount)
                printOutput("Invalid sub-account.");
        }
        else if (bankAccInput == 'E' || bankAccInput == 'e') {
            string inputArr[1];
            printInputArray(inputArr, 1, subCloseInitialize);

            string accType;
            int AccountNum;

            if (inputArr[0].length() >= 7) {
                accType = inputArr->substr(0, 3);
                try {
                    AccountNum = stoi(inputArr->substr(3, 4));
                }
                catch (invalid_argument) { /* do nothing */ }
            }

            bool foundAccount = false;

            if (accType == "SAV") {
                foundAccount = bankAcc->deleteSavingAccount(AccountNum);
            }
            else if (accType == "CHK") {
                foundAccount = bankAcc->deleteCheckingAccount(AccountNum);
            }
            if (foundAccount)
                printOutput("Sub-account " + accType + to_string(AccountNum) + " was successfully closed.");
            else
                printOutput("Invalid sub-account.");
        }
        else if (bankAccInput == 'D' || bankAccInput == 'd') {
            string toPrint[100];
            bankAcc->getDetailedPrint(toPrint);
            for (int x = 0; x < 100; x++) {
                if (toPrint[x].empty())
                    break;
                if (toPrint[x] == "\n") {
                    cout << endl;
                    continue;
                }
                printOutput(toPrint[x]);
            }
        }
        else if (bankAccInput == 'B' || bankAccInput == 'b') {
            printOutput("Aggregated Balance of the bank account : BNK" + to_string(bankAcc->getBankId()) + " with " + to_string(bankAcc->getAccSize()) + " Sub-Accounts is " + to_string(bankAcc->getAggBalance()));
        }
        cout << endl << endl;
    }
    printOutput("End of service for bank-account BNK" + to_string(bankAcc->getBankId()));
}


// Initialize bank menu.

void initializeBank() {
    string bankInfoArray[3];
    printInputArray(bankInfoArray, 3, bankInitialize);
    cout << endl << endl;

    Bank* bank = new Bank(bankInfoArray[0], bankInfoArray[1], bankInfoArray[2]);
    BankAccount* bankAccount = nullptr;
    CheckingAccount* checkingAccount = nullptr;
    SavingAccount* savingAccount = nullptr;

    char mainBankInput = ' ';
    while (mainBankInput != 'X' && mainBankInput != 'x') {
        printServices(bank->getName(), bankService, 9);
        cin >> mainBankInput;

        if (mainBankInput == 'A' || mainBankInput == 'a') {
            printOutput("The number of Bank-Account is " + to_string(BankAccount::bankAccountAmount));
        }
        else if (mainBankInput == 'S' || mainBankInput == 's') {
            printOutput("The number of Saving-Account is " + to_string(SavingAccount::savingAccountAmount));
        }
        else if (mainBankInput == 'H' || mainBankInput == 'h') {
            printOutput("The number of Checking-Account is " + to_string(CheckingAccount::checkingAccountAmount));
        }
        else if (mainBankInput == 'O' || mainBankInput == 'o') {
            cout << endl;
            string inputArr[3];
            printInputArray(inputArr, 3, accountInitialize);
            bankAccount = bank->createNewBankAccount(inputArr[0], inputArr[1], inputArr[2]);
            cout << endl;
            printOutput("A new Bank Account BNK" + to_string(bankAccount->getBankId()) + " was successfully created.");
            cout << endl << endl;
            initializeBankAccount(bankAccount, checkingAccount, savingAccount);
        }
        else if (mainBankInput == 'C' || mainBankInput == 'c') {
            string inputArr[1];
            printInputArray(inputArr, 1, accCloseInitialize);

            string accType;
            int AccountNum;

            if (inputArr[0].length() >= 8) {
                accType = inputArr->substr(0, 3);
                try {
                    AccountNum = stoi(inputArr->substr(3, 5));
                }
                catch (invalid_argument) { /* do nothing */ }
            }

            bool foundAccount = false;

            if (accType == "BNK") {
                foundAccount = bank->getAccount(AccountNum, bankAccount);
            }
            if (foundAccount) {
                bank->deleteAcc(AccountNum);
                printOutput("Bank-account " + accType + to_string(AccountNum) + " was successfully closed.");
            }
            else
                printOutput("Invalid bank-account.");
        }
        else if (mainBankInput == 'M' || mainBankInput == 'm') {
            string inputArr[1];
            printInputArray(inputArr, 1, accModifyInitialize);

            string accType;
            int AccountNum;

            if (inputArr[0].length() >= 8) {
                accType = inputArr->substr(0, 3);
                try {
                    AccountNum = stoi(inputArr->substr(3, 5));
                }
                catch (invalid_argument) { }
            }

            bool foundAccount = false;

            if (accType == "BNK") {
                foundAccount = bank->getAccount(AccountNum, bankAccount);
                if (foundAccount)
                    initializeBankAccount(bankAccount, checkingAccount, savingAccount);
            }
            if (!foundAccount)
                printOutput("Invalid bank-account.");
        }
        else if (mainBankInput == 'D' || mainBankInput == 'd') {
            cout << endl << endl;
            printOutput("Bank Name: " + bank->getName());
            printOutput("Bank Address: " + bank->getAddress());
            printOutput("Bank Working Hours: " + bank->getHours());
            printOutput("Aggregated Balance: " + to_string(bank->getAggBalance()));
            printOutput("Consists of " + to_string(bank->getBankAccounts().size()) + " Bank-Accounts");

            cout << endl << endl;
            for (BankAccount ba : bank->getBankAccounts()) {

                cout << endl << endl;
                printOutput("Bank Account Number: BNK" + to_string(ba.getBankId()));
                printOutput("Account Holder Full Name: " + ba.getName());
                printOutput("Account Holder SSN: " + ba.getSSN());
                printOutput("Aggregated Balance: " + to_string(ba.getAggBalance()));
                printOutput("Consists of " + to_string(ba.getAccSize()) + " Sub-Accounts");

                string toPrint[100];
                ba.getDetailedPrint(toPrint);
                for (int x = 0; x < 100; x++) {
                    if (toPrint[x].empty())
                        break;
                    if (toPrint[x] == "\n") {
                        cout << endl;
                        continue;
                    }
                    printOutput(toPrint[x]);
                }
            }
        }
        else if (mainBankInput == 'B' || mainBankInput == 'b') {
            cout << endl << endl;
            printOutput("Bank Name: " + bank->getName());
            printOutput("Bank Address: " + bank->getAddress());
            printOutput("Bank Working Hours: " + bank->getHours());
            printOutput("Aggregated Balance: " + to_string(bank->getAggBalance()));
            printOutput("Consists of " + to_string(bank->getBankAccounts().size()) + " Bank-Accounts");
            for (BankAccount ba : bank->getBankAccounts()) {
                printOutput("Aggregated Balance of the bank account : BNK" + to_string(ba.getBankId()) + " with " +
                    to_string(ba.getAccSize()) + " Sub-Accounts is " +
                    to_string(ba.getAggBalance()));
            }
        }
        cout << endl << endl;
    }

    printOutput("End of service for bank " + bank->getName());
      
}


int main() {

    initializeBank();

    return 0;
}