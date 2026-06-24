#include "ReadWriteLock.h"

#include <mutex>
//
// Created by bartali on 22/06/2026.
//
ReadWriteLock::ReadWriteLock() {
    pthread_mutex_init(&this->lock,nullptr);
    pthread_cond_init(&this->can_write,nullptr);
    pthread_cond_init(&this->can_read,nullptr);
}
void ReadWriteLock::readLock() {
    pthread_mutex_lock(&lock);
    while (active_writer || waiting_writers > 0) {
        pthread_cond_wait(&can_read, &lock);
    }
    active_readers++;
    pthread_mutex_unlock(&lock);
}


void ReadWriteLock::writeLock() {
    pthread_mutex_lock(&this->lock);
    waiting_writers++;
    while (active_readers > 0 || active_writer) {
        pthread_cond_wait(&can_write, &lock);
    }
    waiting_writers--;
    active_writer = true;
    pthread_mutex_unlock(&this->lock);
}

void ReadWriteLock::readUnlock() {
    pthread_mutex_lock(&this->lock);
    active_readers--;
    if (active_readers == 0) {
        pthread_cond_signal(&can_write);
    }
    pthread_mutex_unlock(&this->lock);
}

void ReadWriteLock::writeUnlock() {
    pthread_mutex_lock(&this->lock);
    active_writer = false;
    if (waiting_writers > 0) {
        pthread_cond_signal(&can_write);
    } else {
        pthread_cond_broadcast(&can_read);
    }
    pthread_mutex_unlock(&lock);
}

ReadWriteLock::~ReadWriteLock() {
    pthread_cond_destroy(&readers_cond);
    pthread_cond_destroy(&writers_cond);
    pthread_mutex_destroy(&lock);
}