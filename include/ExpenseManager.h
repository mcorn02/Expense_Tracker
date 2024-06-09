//
// Created by Michael Corn on 5/30/24.
//

#ifndef EXPENSE_TRACKER_EXPENSEMANAGER_H
#define EXPENSE_TRACKER_EXPENSEMANAGER_H
#include "Expense.h"
#include "vector"
#include <fstream>

class ExpenseManager {
private:
    std::vector<Expense> expenseVector;
    std::string fileName;
public:
    ExpenseManager();
    void printExpenseVector();
    void mainMenu();
    void addExpense();

    std::string categoryToString(Category category);
    Category stringToCategory(std::string& str);

    bool validateDateInput(std::string& inp);
    Category selectCategory();
    void writeExpensesToCSV(std::vector<Expense>& expenses, const std::string& filename);
    std::vector<Expense> openExpensesCSV(std::string fileName);

    void generateRandomExpenses(int numExpenses);
    long double generateRandomLongDouble();
};


#endif //EXPENSE_TRACKER_EXPENSEMANAGER_H
