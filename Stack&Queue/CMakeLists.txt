cmake_minimum_required(VERSION 3.17)
project(Stack_Queue)

set(CMAKE_CXX_STANDARD 14)

add_executable(Stack_Queue main.cpp DoubleLinkedList.h Stack.h Queue.h)