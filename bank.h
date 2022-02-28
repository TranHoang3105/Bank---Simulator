#ifndef BANK_H
#define BANK_H

#include "account.h"
#include <vector>

class Bank {
public:
   
    Bank(string name, string address, string workingHours) {
        this->name = name;
        this->address = address;
        this->workingHours = workingHours;
    }

   
    string getName() { return name; }
   
    string getAddress() { return address; }
    
    string getHours() { return workingHours; }

    // Create a bank account.
    BankAccount* createNewBankAccount(string firstName, string lastName, string ssn) {
        bankAccounts.push_back(BankAccount(firstName, lastName, ssn));
        return &bankAccounts.at(bankAccounts.size() - 1);
    }

   
    const vector<BankAccount> getBankAccounts() { return bankAccounts; }

 
    int getAggBalance() {
        int aggBal = 0;
        for (BankAccount ba : bankAccounts) { aggBal += ba.getAggBalance(); }
        return aggBal;
    }

    
    bool getAccount(int id, BankAccount*& bAcc) {
        for (int i = 0; i < bankAccounts.size(); i++) {
            if (bankAccounts.at(i).getBankId() == id) {
                bAcc = &bankAccounts.at(i);
                return true;
            }
        }
        return false;
    }

    // Delete bank account corresponding to the bank ID.

    bool deleteAcc(int id) {
        for (vector<BankAccount>::iterator it = bankAccounts.begin(); it != bankAccounts.end(); ++it) {
            if (it->getBankId() == id) {
                bankAccounts.erase(it);
                return true;
            }
        }
        return false;
    }

protected:
    string name;
    string address;
    string workingHours;
    vector<BankAccount> bankAccounts;

};

#endif
