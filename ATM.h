//
// Created by bartali on 22/06/2026.
//
#pragma once
#include <pthread.h>
#include "Account.h"
#include <iostream>
using std::ostream;

class Operation {

    public:
};
class ATM {
    pthread_t Worker;
    unsigned ATM_ID;
    string filePath;
public:
    friend class Bank;
    ostream executeOperation(Operation& operation);

};
