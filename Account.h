//
// Created by bartali on 22/06/2026.
//
#pragma once
#include <cstring>

#include "ReadWriteLock.h"
#include <string>
using std::string;
class ATM;
enum Currency {USD, ILS};
struct Balance {
    double usd_balance=0;
    double ils_balance=0;
    Balance(double usd, double ils) : usd_balance(usd), ils_balance(ils) {}
};
class Account {
    unsigned ID;
    string password;
    Balance balance;
    ReadWriteLock lock;
    bool hasEnough(double amount, Currency currency) const;
    bool deposit(double amount, Currency currency);
    bool withdraw(double amount, Currency currency);
    bool exchange(Currency source, Currency target, double amount);
public:
    friend class ATM;
    Account(unsigned id,const string& password, double ils_balance, double usd_balance): ID(id), balance(ils_balance,usd_balance) {
       this->password = password;
    };
    bool checkPassword(string password) const; //V
    Balance getBalance() const; //V
    unsigned getId() const; //V
};

 bool Account::checkPassword(string password) const {
    if (password == this->password) {
        return true;
    } else {
        return false;
    }
}


unsigned Account::getId() const {
    return ID;
}
 Balance Account::getBalance() const{
     return balance;
 }

bool Account::hasEnough(double amount, Currency currency) const {
    if (currency == USD) {
        if (amount > balance.usd_balance) {
            return false;
        } else {
            return true;
        }
    } else {
        if (amount > balance.ils_balance) {
            return false;
        } else {
            return true;
        }
    }
}

bool Account::deposit(double amount, Currency currency){
     if (!amount) {
         return false;
     }
    if (currency == USD) {
        balance.usd_balance += amount;
        return true;
    } else {
        balance.ils_balance += amount;
        return true;
    }
}

 bool Account::withdraw(double amount, Currency currency) {
     if (hasEnough(amount,currency)) {
         if (currency == USD) {
             balance.usd_balance -= amount;
             return true;
         }else {
             balance.ils_balance -= amount;
             return true;
         }
     }
     return false;
 }

bool Account::exchange(Currency source, Currency target, double amount) {
    if (hasEnough(amount,source)) {
        if (source==USD) {
            balance.usd_balance -= amount;
            balance.ils_balance += 5*amount;
            return true;
        } else {
            balance.ils_balance -= amount;
            balance.usd_balance += amount / 5;
            return true;
        }
    }
     return false;
}
