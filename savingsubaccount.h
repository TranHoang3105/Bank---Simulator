#ifndef SAVINGSUBACCOUNT_H
#define SAVINGSUBACCOUNT_H

#include "account.h"

class SavingAccount : public Account {
public:
    static int savingAccountAmount;

   SavingAccount(int initBal) {
        setBankId(1000 + savingAccountAmount);
        initializeBal(initBal);
        savingAccountAmount++;
    }
};

#endif
