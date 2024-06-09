//
// Created by Michael Corn on 5/30/24.
//

#include "../include/Expense.h"
Expense::Expense(std::string date, Category category, std::string description, long double amount)
: expenseDate(date), expenseCategory(category), expenseDescription(description), expenseAmount(amount) {}

Expense::Expense() : expenseDate(""), expenseCategory(Category::OTHER), expenseDescription(""), expenseAmount(0.0) {}

Category Expense::getExpenseCategory()
{
    return expenseCategory;
}

void Expense::setExpenseCategory(Category category)
{
    expenseCategory = category;
}

std::string Expense::getExpenseDescription()
{
    return expenseDescription;
}

void Expense::setExpenseDescription(std::string name)
{
    expenseDescription = name;
}

std::string Expense::getExpenseDate()
{
    return expenseDate;
}

void Expense::setExpenseDate(std::string date)
{
    expenseDate = date;
}

long double Expense::getExpenseAmount()
{
    return expenseAmount;
}

void Expense::setExpenseAmount(long double amount)
{
    expenseAmount = amount;
}