#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "account.h"

class CheckingAccount : public Account {
public:
    static int checkingAccountAmount;

    
    CheckingAccount(int initBal, int maxCap, bool locked) {
        setBankId(6000 + checkingAccountAmount);

        initializeBal(initBal);
        this->maxCap = maxCap;
        this->locked = locked;

        checkingAccountAmount++;
    }

    int getCap() { return maxCap; }
   
    bool isLocked() { return locked; }
   
    void setLocked(bool lock) { this->locked = lock; }
   
    void setCap(int cap) { this->maxCap = cap; }

private:
    int maxCap;
    bool locked;
};

#endif
