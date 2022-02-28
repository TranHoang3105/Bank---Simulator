#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
public:
    
    void setBankId(int toId) { this->id = toId; }

    int getBankId() { return id; }

    void initializeBal(int initAmount) {
        this->balance = initAmount;
    }
   
    void deposit(int depositAmount) {
        this->balance += depositAmount;
    }
    
    void withdraw(int withdrawAmount) {
        this->balance -= withdrawAmount;
    }
    
    int getBalance() {
        return balance;
    }

private:
    int balance;
    int withdrawAmount;
    int initAmount;
    int id;

};

#endif
