//
// Created by Michael Corn on 5/30/24.
//

#ifndef EXPENSE_TRACKER_EXPENSE_H
#define EXPENSE_TRACKER_EXPENSE_H
#include "iostream"
#include "Category.h"

class Expense {
private:
    std::string expenseDate;
    Category expenseCategory;
    std::string expenseDescription;
    long double expenseAmount;
public:
    Expense(std::string date, Category category, std::string description, long double amount);
    Expense();
    std::string getExpenseDate();
    void setExpenseDate(std::string date);
    Category getExpenseCategory();
    void setExpenseCategory(Category category);
    std::string getExpenseDescription();
    void setExpenseDescription(std::string description);
    long double getExpenseAmount();
    void setExpenseAmount(long double amount);
};

#endif //EXPENSE_TRACKER_EXPENSE_H
