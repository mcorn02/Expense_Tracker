cmake_minimum_required(VERSION 3.27)
project(Expense_Tracker)

set(CMAKE_CXX_STANDARD 17)

add_executable(Expense_Tracker src/main.cpp
        src/Expense.cpp
        include/Expense.h
        src/ExpenseManager.cpp
        include/ExpenseManager.h
        src/Category.cpp
        include/Category.h
)
