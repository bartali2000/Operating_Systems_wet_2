//
// Created by bartali on 22/06/2026.
//
#pragma once
#include <string>
#include "ReadWriteLock.h"

using std::string;
class ATM;

enum Currency {
    USD,
    ILS
};

struct Balance {
    double usd_balance;
    double ils_balance;
    Balance(double usd = 0, double ils = 0): usd_balance(usd), ils_balance(ils) {}
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
    Account(unsigned id,const string& password,double ils_balance,double usd_balance): ID(id),password(password),balance(usd_balance, ils_balance) {}
    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;
    bool checkPassword(const string& password) const;
    Balance getBalance() const;
    unsigned getId() const;
    void readLock();
    void readUnlock();
    void writeLock();
    void writeUnlock();
};

inline bool Account::checkPassword(const string& password) const {
    return this->password == password;
}

inline unsigned Account::getId() const {
    return ID;
}

inline Balance Account::getBalance() const {
    return balance;
}

inline bool Account::hasEnough(double amount, Currency currency) const {
    if (currency == USD) {
        return amount <= balance.usd_balance;
    } else {
        return amount <= balance.ils_balance;
    }
}

inline bool Account::deposit(double amount, Currency currency) {
    if (!amount) {
        return false;
    }
    if (currency == USD) {
        balance.usd_balance += amount;
    } else {
        balance.ils_balance += amount;
    }

    return true;
}

inline bool Account::withdraw(double amount, Currency currency) {
    if (!hasEnough(amount, currency)) {
        return false;
    }

    if (currency == USD) {
        balance.usd_balance -= amount;
    } else {
        balance.ils_balance -= amount;
    }

    return true;
}

inline bool Account::exchange(Currency source, Currency target, double amount) {
    if (!hasEnough(amount, source)) {
        return false;
    }
    if (source == target) {
        return true;
    }
    if (source == USD && target == ILS) {
        balance.usd_balance -= amount;
        balance.ils_balance += 5 * amount;
        return true;
    }
    if (source == ILS && target == USD) {
        balance.ils_balance -= amount;
        balance.usd_balance += amount / 5;
        return true;
    }
    return false;
}

inline void Account::readLock() {
    lock.readLock();
}

inline void Account::readUnlock() {
    lock.readUnlock();
}

inline void Account::writeLock() {
    lock.writeLock();
}

inline void Account::writeUnlock() {
    lock.writeUnlock();
}