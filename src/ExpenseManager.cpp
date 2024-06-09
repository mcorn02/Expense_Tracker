//
// Created by Michael Corn on 5/30/24.
//
#include "../include/ExpenseManager.h"
#include "string"
#include "iomanip"
#include "regex"
#include <sstream>
using namespace std;

ExpenseManager::ExpenseManager()
{
    fileName = "expenses.csv";
    mainMenu();
}

void ExpenseManager::mainMenu()
{
    cout << "WELCOME TO EXPENSE TRACKER\n";
    cout << "--------------------------\n";

    int choice;

    do{
        cout << "Enter 1 to add expense\nEnter 2 to print expenses"
                "\nEnter 3 to open CSV file with expenses\nEnter 4 to generate expenses"
                "\nEnter 99 to quit\n";
        cout << "--------------------------\n";
        cin >> choice;

        switch (choice) {
            case 1: {
                addExpense();
                break;
            }
            case 2: {
                printExpenseVector();
                break;
            }
            case 3: {
                cout << "File: " << fileName << "\n";
                openExpensesCSV(fileName);
            }
            case 4: {
                int numExpenses;
                cout << "Enter how many expenses you would like to generate\n";
                cin >> numExpenses;
                generateRandomExpenses(numExpenses);
                break;
            }
            case 99: {
                exit(0);
            }
            default: {
                cout << "Invalid input please try again.\n";
                break;
            }
        }
    } while (choice!=99);
}

//adds expense to the expenseVector
void ExpenseManager::addExpense()
{
    string date, description;
    long double amount;

    do {
        cout << "Enter the date of the expense (MM/DD/YYYY):\n";
        cin >> date;
    } while (!validateDateInput(date));

    Category category = selectCategory();

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Enter the description of the expense (ex: Car Payment)\n";
    getline(cin, description);

    cout << "Enter the amount of the expense (ex: 123.45)\n";
    cin >> amount;

    Expense myExpense(date, category, description, amount);
    expenseVector.emplace_back(myExpense);
    writeExpensesToCSV(expenseVector, fileName);

    cout << "Expense added successfully.\n";
}

//prints all expenses
void ExpenseManager::printExpenseVector()
{
    cout << "--------------------------\n";
    if(expenseVector.empty()) {
        cout << "No expenses found\n";
    }

    for(auto& expense : expenseVector)
    {
        cout << "Date: " << expense.getExpenseDate() << " \nCategory: " << categoryToString(expense.getExpenseCategory()) << " \nNotes: " << expense.getExpenseDescription()
        << " \nAmount: $" << fixed << setprecision(2) << expense.getExpenseAmount() << "\n";
        cout << "\n";
    }
    cout << "--------------------------\n";
}

//checks the date is of MM/DD/YYYY format
bool ExpenseManager::validateDateInput(std::string& inp)
{
    std::regex datePattern(R"(^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/(\d{4})$)");

    if(regex_match(inp, datePattern))
    {
        //check if days of month are valid
        int month = stoi(inp.substr(0, 2));
        int day = stoi(inp.substr(3, 2));
        int year = stoi(inp.substr(6, 4));

        bool valid = true;
        switch (month) {
            case 2: // February
                if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                {
                    valid = day <= 29; // Leap year
                }
                else {
                    valid = day <= 28; // Non-leap year
                }
                break;
            case 4: case 6: case 9: case 11: // April, June, September, November
                valid = day <= 30;
                break;
            default: // All other months (January, March, May, July, August, October, December)
                valid = day <= 31;
                break;
        }
        return valid;
    }
    return false;
}

//handles expense category selection
Category ExpenseManager::selectCategory()
{
    int categoryChoice;
    cout << "Please select the expense category\n";
    cout << "Enter 1 for FOOD\nEnter 2 for TRANSPORTATION\nEnter 3 for ENTERTAINMENT\n"
            "Enter 4 for HEALTH\nEnter 5 for BILL\nEnter 6 for Education\nEnter 7 for OTHER\n";
    cin >> categoryChoice;

    switch (categoryChoice) {
        case 1: return Category::FOOD;
        case 2: return Category::TRANSPORTATION;
        case 3: return Category::ENTERTAINMENT;
        case 4: return Category::HEALTH;
        case 5: return Category::BILL;
        case 6: return Category::EDUCATION;
        case 7: return Category::OTHER;
        default: return Category::OTHER;
    }
}

//handles enum conversion
std::string ExpenseManager::categoryToString(Category category) 
{
    switch (category) {
        case Category::FOOD: return "Food";
        case Category::TRANSPORTATION: return "Transportation";
        case Category::ENTERTAINMENT: return "Entertainment";
        case Category::HEALTH: return "Health";
        case Category::BILL: return "Bill";
        case Category::EDUCATION: return "Education";
        case Category::OTHER: return "Other";
        default: return "Unknown";
    }
}

//handles string to enum conversion
Category ExpenseManager::stringToCategory(std::string &str) 
{
    if(str == "Food") return Category::FOOD;
    if(str == "Transportation") return Category::TRANSPORTATION;
    if(str == "Entertainment") return Category::ENTERTAINMENT;
    if(str == "Health") return Category::HEALTH;
    if(str == "Bill") return Category::BILL;
    if(str == "Education") return Category::EDUCATION;
    if(str == "Other") return Category::OTHER;
    throw invalid_argument("Unknown category: " + str);
}

void ExpenseManager::writeExpensesToCSV(std::vector<Expense> &expenses, const std::string &filename)
{
    //check if file exists first
    bool fileExists = false;
    ifstream checkFile(fileName);
    if(checkFile.is_open() && checkFile.peek() != ifstream::traits_type::eof()) {
        fileExists = true;
    }
    checkFile.close();

    ofstream outFile(filename, ios::app); //append mode to add to existing file
    if(!outFile.is_open())
    {
        cerr << "Error opening file: " << filename << "\n";
        return;
    }

    //add headers if the file doesn't exist
    if(!fileExists) {
        outFile << "Date,Amount,Category,Description\n";
    }

    for(auto& expense : expenseVector)
    {
        outFile << expense.getExpenseDate() << ","
        << expense.getExpenseAmount() << ","
        << categoryToString(expense.getExpenseCategory()) << ","
        << expense.getExpenseDescription() << "\n";

    }

    outFile.close();
    cout << "Expenses written to " << filename << " successfully.\n";
}

std::vector<Expense> ExpenseManager::openExpensesCSV(std::string fileName)
{
    vector<Expense> expenses;
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return expenses;
    }

    string line;
    // Skip the header line
    if (!getline(inFile, line)) {
        cerr << "Error reading the header line from the file: " << fileName << endl;
        return expenses;
    }

    while (getline(inFile, line)) {
        if (line.empty()) {
            continue; //Skip empty lines
        }

        stringstream ss(line);
        string token;
        Expense expense;

        //Read each token separated by commas
        getline(ss, token, ',');
        if (token.empty() || token == "Date") {
            cerr << "Empty or invalid date value in line: " << line << endl;
            continue;
        }
        expense.setExpenseDate(token);

        getline(ss, token, ',');
        try {
            if (token.empty() || token == "Amount") {
                throw invalid_argument("Empty or invalid amount value");
            }
            expense.setExpenseAmount(stold(token)); //Convert string to long double
        } catch (const invalid_argument& e) {
            cerr << "Invalid amount value: " << token << " in line: " << line << endl;
            continue;
        }

        getline(ss, token, ',');
        try {
            if (token.empty() || token == "Category") {
                throw invalid_argument("Empty or invalid category value");
            }
            expense.setExpenseCategory(stringToCategory(token));
        } catch (const invalid_argument& e) {
            cerr << "Invalid category value: " << token << " in line: " << line << endl;
            continue;
        }


        getline(ss, token);
        if (token.empty() || token == "Description") {
            cerr << "Empty or invalid description value in line: " << line << endl;
            continue;
        }
        expense.setExpenseDescription(token);

        expenses.push_back(expense);
    }

    inFile.close();

    //Print all expenses
    for (auto& expense : expenses) {
        cout << "Date: " << expense.getExpenseDate() << "\n"
             << "Amount: $" << expense.getExpenseAmount() << "\n"
             << "Category: " << categoryToString(expense.getExpenseCategory()) << "\n"
             << "Description: " << expense.getExpenseDescription() << "\n\n";
    }

    return expenses;
}

//generates expenses
void ExpenseManager::generateRandomExpenses(int numExpenses)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    for(int i = 0; i < numExpenses; i++)
    {
        int month = rand() % 12 + 1;
        int day = rand() % 28 + 1;
        int year = 2022 + rand() % 3;

        string date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);

        long double amount = generateRandomLongDouble();

        string description = "Test Description " + to_string(i+1);

        Category category = static_cast<Category>(rand() % static_cast<int>(Category::OTHER));

        Expense myExpense(date, category, description, amount);

        expenseVector.emplace_back(myExpense);
    }
    writeExpensesToCSV(expenseVector, fileName);
}

long double ExpenseManager::generateRandomLongDouble()
{
    long double upperBound = 1000;
    long double lowerBound = 0;

    long double random = (static_cast<long double>(rand()) / RAND_MAX) * (upperBound - lowerBound) + lowerBound;

    random = round((random * 100) / 100);

    return random;
}