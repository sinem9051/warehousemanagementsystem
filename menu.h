#ifndef MENU_H
#define MENU_H

#include "Manager.h"
#include "Employee.h"

class Menu {
private:
    int userType;

    Manager manager;
    Employee employee;

    public:
    
	Menu();

    void showMainMenu();
    bool authenticateManager();
    bool authenticateEmployee();

    void showManagerMenu();
    void showEmployeeMenu();

    void writeManagerDataToFile() const;
    void readManagerDataFromFile();
    void writeEmployeeDataToFile() const;
    void readEmployeeDataFromFile();
    void readShelfDataFromFile();
};

#endif 
