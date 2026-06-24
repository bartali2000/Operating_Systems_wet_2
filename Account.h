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
    int usd_balance=0;
    int ils_balance=0;
};
class Account {
    int ID;
    string password;
    Balance balance;
    ReadWriteLock lock;
    public:
    friend class ATM;
    Account(int id, int password, int ils_balance, int usd_balance): ID(id), password(password), usd_balance(usd_balance) {};
    bool checkPassword(int password) const;
    Balance getBalance() const;
    bool hasEnough(int amount, Currency currency) const;
    void deposit(int amount, Currency currency);
    void withdraw(int amount, Currency currency);
    void exchange(Currency source, Currency target, int amount);
    int getId() const;
    int getPassword() const;
};

 bool Account::checkPassword(string password) const {
    if (strcmp(password,this->password) == 0) {
        return true;
    } else {
        return false;
    }
}



Balance getBalance() {

}

bool hasEnough(int amount, Currency currency) const;
void deposit(int amount, Currency currency);
void withdraw(int amount, Currency currency);

void exchange(Currency source, Currency target, int amount);

int getId() const;
int getPassword() const;