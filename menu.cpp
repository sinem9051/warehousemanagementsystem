#include "Menu.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

const string MANAGER_FILE = "manager.txt";  
const string EMPLOYEE_FILE = "employee.txt";  

Menu::Menu() : manager(), employee(manager) {
    
}

void Menu::showMainMenu() {
    int userType;
    char input;

    do {
        cout << "Select User Type:" << endl;
        cout << "1. Manager" << endl;
        cout << "2. Employee" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> input;

        if (isdigit(input)) {
            userType = input - '0';

            switch (userType) {
                case 0:
                    cout << "Exiting program. Goodbye!" << endl;
                    return;
                case 1:
                    if (authenticateManager()) {
                        readManagerDataFromFile();
                        showManagerMenu();
                        writeManagerDataToFile();
                    } else {
                        cout << "Authentication failed. Please try again." << endl;
                    }
                    break;
                case 2:
                    if (authenticateEmployee()) {
                        readEmployeeDataFromFile();
                        showEmployeeMenu();
                        writeEmployeeDataToFile();
                    } else {
                        cout << "Authentication failed. Please try again." << endl;
                    }
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (userType != 0);
}

bool Menu::authenticateManager() {
    string enteredUsername, enteredPassword;
    cout << "Enter manager username: ";
    cin >> enteredUsername;

    ifstream managerFile(MANAGER_FILE);
    if (!managerFile.is_open()) {
        cerr << "Unable to open manager file for authentication." << endl;
        return false;
    }

    string storedUsername, storedPassword;
    managerFile >> storedUsername >> storedPassword;
    managerFile.close();

    if (enteredUsername == storedUsername) {
        cout << "Username is correct." << endl;

        cout << "Enter manager password: ";
        cin >> enteredPassword;

        if (enteredPassword == storedPassword) {
            cout << "Password is correct." << endl;
            return true;
        } else {
            cout << "Incorrect password." << endl;
            return false;
        }
    } else {
        cout << "Incorrect username." << endl;
        return false;
    }
}

bool Menu::authenticateEmployee() {
    string enteredUsername, enteredPassword;
    cout << "Enter employee username: ";
    cin >> enteredUsername;

    ifstream employeeFile(EMPLOYEE_FILE);
    if (!employeeFile.is_open()) {
        cerr << "Unable to open employee file for authentication." << endl;
        return false;
    }

    string storedUsername, storedPassword;
    employeeFile >> storedUsername >> storedPassword;
    employeeFile.close();

    if (enteredUsername == storedUsername) {
        cout << "Username is correct." << endl;

        cout << "Enter employee password: ";
        cin >> enteredPassword;

        if (enteredPassword == storedPassword) {
            cout << "Password is correct." << endl;
            return true;
        } else {
            cout << "Incorrect password." << endl;
            return false;
        }
    } else {
        cout << "Incorrect username." << endl;
        return false;
    }
}

void Menu::showManagerMenu() {
    int choice;

    do {
        cout << "Manager Menu:" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. View Products" << endl;
        cout << "3. Remove Product" << endl;
        cout << "4. Modify Product" << endl;
        cout << "5. Shelve Management" << endl;
        cout << "6. Exit to Main Menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addProduct();
                break;
            case 2:
                manager.viewProducts();
                break;
            case 3:
                manager.removeProduct();
                break;
            case 4:
                manager.modifyProduct();
                break;
            case 5:
                readShelfDataFromFile();
                break;
            
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

void Menu::showEmployeeMenu() {
    int choice;

    do {
        cout << "Employee Menu:" << endl;
        cout << "1. Create Order" << endl;
        cout << "2. View Orders" << endl;
        cout << "3. Prepare Order" << endl;
        cout << "0. Back to menu" << endl;


        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                employee.createOrder();
                break;
            case 2:
                employee.viewOrders();
                break;
            case 3:
                employee.prepareOrder();
                break;
           
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void Menu::writeManagerDataToFile() const {
    manager.writeToFile();
}

void Menu::readManagerDataFromFile() {
    manager.readFromFile();
}

void Menu::writeEmployeeDataToFile() const {
    employee.writeOrdersToFile();
}

void Menu::readEmployeeDataFromFile() {
    employee.readOrdersFromFile();
}

void Menu::readShelfDataFromFile() {
    ifstream file("shelf.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open shelf data file." << endl;
    }
}
