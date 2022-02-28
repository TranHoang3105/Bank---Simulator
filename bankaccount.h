#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "checkingaccount.h"
#include "savingsubaccount.h"
#include <vector>

class BankAccount : public Account {
public:
    static int bankAccountAmount;

    
    BankAccount(string firstName, string lastName, string ssn) {
        setBankId(10000 + bankAccountAmount);
        name = firstName + " " + lastName;
        this->ssn = ssn;
        bankAccountAmount++;
    }

    string getName() { return name; }
   
    string getSSN() { return ssn; }
    
   // Create new Checking Account.
    
    CheckingAccount* createNewCheckingAccount(int initBal, int maxCap, bool locked) {
        checkingAccs.push_back(CheckingAccount(initBal, maxCap, locked));
        return &checkingAccs.at(checkingAccs.size() - 1);
    }

    
    SavingAccount* createNewSavingAccount(int initBal) {
        if (savingAccs.size() == 0)
            savingAccs.push_back(SavingAccount(initBal + 100));
        else
            savingAccs.push_back(SavingAccount(initBal));
        return &savingAccs.at(savingAccs.size() - 1);
    }

    
    bool getCheckingAccount(int id, CheckingAccount*& cAcc) {
        for (int x = 0; x < checkingAccs.size(); x++) {
            if (checkingAccs.at(x).getBankId() == id) { cAcc = &checkingAccs.at(x); return true; }
        }
        return false;
    }

    // Get saving acc for corresponding bank ID.
    bool getSavingAccount(int id, SavingAccount*& sAcc) {
        for (int x = 0; x < savingAccs.size(); x++) {
            if (savingAccs.at(x).getBankId() == id) { sAcc = &savingAccs.at(x); return true; }
        }
        return false;
    }

   // Delete checking account for corresponding bank ID.
    bool deleteCheckingAccount(int id) {
        vector<CheckingAccount>::iterator it;
        for (it = checkingAccs.begin(); it != checkingAccs.end(); ++it) {
            if (it->getBankId() == id) { checkingAccs.erase(it); return true; }
        }
        return false;
    }

   // Delete saving acc for corresponding bank ID
    bool deleteSavingAccount(int id) {
        vector<SavingAccount>::iterator it;
        for (it = savingAccs.begin(); it != savingAccs.end(); ++it) {
            if (it->getBankId() == id) { savingAccs.erase(it); return true; }
        }
        return false;
    }

   
    int getAccSize() { 
        return savingAccs.size() + checkingAccs.size(); 
    }

  
    int getAggBalance() {
        int aggBal = 0;
        for (SavingAccount a : savingAccs) { aggBal += a.getBalance(); }
        for (CheckingAccount a : checkingAccs) { aggBal += a.getBalance(); }
        return aggBal;
    }

    
    void getDetailedPrint(string inputArr[100]) {
        int x = 0;
        for (SavingAccount savAcc : savingAccs) {
            inputArr[x] = "\n";
                x++;
            inputArr[x] = "Sub-Account number: SAV" + to_string(savAcc.getBankId());
                x++;
            inputArr[x] = "Balance: " + to_string(savAcc.getBalance());
                x++;
            inputArr[x] = "\n";
        }
        for (CheckingAccount cheAcc : checkingAccs) {
            inputArr[x] = "\n";
                x++;
            inputArr[x] = "Sub-Account number: CHK" + to_string(cheAcc.getBankId());
                x++;
            inputArr[x] = "Balance: " + to_string(cheAcc.getBalance());
                x++;
            inputArr[x] = "\n";
                x++;
            inputArr[x] = "The maximum capacity is: " + to_string(cheAcc.getCap());
                x++;

            string b = "";
            if (!cheAcc.isLocked())
                b = "not ";

            inputArr[x] = "The sub-account is " + b + "locked.";
                x++;
            inputArr[x] = "\n";
        }
    }

private:
    string name;
    string ssn;
    vector<SavingAccount> savingAccs;
    vector<CheckingAccount> checkingAccs;
};

#endif
