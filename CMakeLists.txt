cmake_minimum_required(VERSION 4.2)
project(Wet_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Wet_2
        bank.cpp
        ATM.cpp
        Account.h
        ATM.h
        ReadWriteLock.h
        ReadWriteLock.cpp)
