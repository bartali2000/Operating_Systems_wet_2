//
// Created by bartali on 22/06/2026.
//
#include <pthread.h>
#pragma once

class ReadWriteLock {
    pthread_mutex_t lock;
    pthread_cond_t can_read;
    pthread_cond_t can_write;

    int active_readers= 0;
    int waiting_writers = 0;
    bool active_writer = false;

public:
    ReadWriteLock();
    ~ReadWriteLock();
    void readLock();
    void readUnlock();
    void writeLock();
    void writeUnlock();
    ReadWriteLock(const ReadWriteLock&) = delete;
    ReadWriteLock& operator=(const ReadWriteLock&) = delete;
};