#include <iostream>
#include "Employee.h"
#include "ProductionWorker.h"
#include "Manager.h"
#include "Session.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std; 

/// manually instantiate a manager and a couple of employees ///

int main(){
    vector<ProductionWorker> employees;
    vector<Manager> managers;

    Manager manager(30.50, "nmcalister", "password123");
    managers.push_back(manager);

    ProductionWorker employee1("Jonny Yur", 1, "11/12/2018", 1, 25.50);
    ProductionWorker employee2("Kim Tarminsk", 2, "05/14/2016", 2, 24.00);
    ProductionWorker employee3("John Doe", 3, "08/25/2010", 2, 26.70);
    ProductionWorker employee4("Jane Doe", 4, "09/13/2023", 1, 20.50);
    employees.push_back(employee1);
    employees.push_back(employee2);
    employees.push_back(employee3);
    employees.push_back(employee4);

    bool authUsernameAndPassword = false;
    string checkUsername = "";
    string checkPassword = "";

    Session session;

    do {
        cout << "--- Enter Your Login Credentials ---" << endl; 
        cout << "Username: ";
        cin >> checkUsername;
        cout << "Password: "; 
        cin >> checkPassword; 

        for (int i = 0; i < managers.size(); i++){
            if (managers[i].getUsername() == checkUsername && managers[i].getPassword() == checkPassword){
                authUsernameAndPassword = true;
                session.setUser(managers[i].getUsername());
            } else {
                cout << "\n\n";
                cout << "Your login credentials are not valid, please try again.\n" << endl;
            }
        }
    } while (authUsernameAndPassword == false);

    int choice; 
    int updateEmployeeChoice; 
    int choiceTwo = 0; 
    int choiceThree = 0;
    int employeeChoice; 
    ProductionWorker newWorker;
    Manager newManager; 

    string employeeToManagerName; 
    int employeeToManagerBool; 
    /// Production Worker ///
    string name; 
    int number; 
    string hireDate;
    int shift;
    double hourlyPayRate; 

    double newHourlyPayRate;
    int newShift;

    /// Manager ///
    float salary; 
    string username; 
    string password; 

    float newSalary; 
    string newUsername; 
    string newPassword; 

    int indexToDelete;

    time_t logouttime; 

    ofstream outputFile("log.txt");

    cout << "\n--- Welcome " << checkUsername << " ---\n"<< endl; 

    do {
        cout << "Menu:\n";
        cout << "1. View Current Employees\n";
        cout << "2. Update an Employee\n";
        cout << "3. Create New Employee\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                /// View all employees ///
                for (int i = 0; i < employees.size(); i++){
                    cout << "Employee Name: " << employees[i].getName() << endl; 
                    cout << "Employee Number: " << employees[i].getNumber() << endl; 
                    cout << "Employee Hire Date: " << employees[i].getHireDate() << endl; 
                    cout << "Employee Shift: " << employees[i].getShift() << endl; 
                    cout << "Employee Hourly Pay Rate: " << employees[i].getHourlyPayRate() << endl; 
                    cout << "\n";
                }
                break;
            case 2:
                /// Update an employee ///
                cout << "\nYou selected to update an employee." << endl; 
                do {
                    cout << "Menu to Update Employee:\n";
                    cout << "1. Assign Employee to a Manager\n";
                    cout << "2. Update Employee Pay\n";
                    cout << "3. Change Employee Shift\n";
                    cout << "4. Exit\n";

                    cout << "Enter your choice: ";
                    cin >> updateEmployeeChoice;
                    //cin.ignore();

                    switch(updateEmployeeChoice){
                        case 1:
                            // assign employee to manager
                            
                            do {
                                cout << "\nYou selected to assign an employee to a manager.\n";
                                cout << "Enter the employee's name that you would like to change to a manager." << endl; 
                                cout << "Here is the list of employees names:" << endl; 
                                for (int i = 0; i < employees.size(); i++){
                                    cout << employees[i].getName() << endl; 
                                }
                                cin.ignore();
                                cout << "Enter their name: ";
                                getline(cin, employeeToManagerName);
                                cout << "Are you sure that this is the employee that you want to change to become a manager?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                cin >> employeeToManagerBool;
                            } while(employeeToManagerBool != 1);
                            for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        // create manager object
                                        indexToDelete = i; 
                                        do {
                                            cout << "\n";
                                            cout << "You have selected to create a new manager." << endl; 
                                            cout << "Manager Salary (60000.00): "; 
                                            cin >> newSalary; 
                                            cout << "Manager Username (newuser123 [no spaces allowed]): ";
                                            cin >> newUsername; 
                                            cout << "Manager Password (password123 [no spaces allowed]): ";
                                            cin >> newPassword; 

                                            cout << "\n";
                                            cout << "These are the values you provided:" << endl; 
                                            cout << "Salary: " << newSalary << endl;
                                            cout << "Username: " << newUsername << endl;
                                            cout << "Password: " << newPassword << endl;
                                            cout << "\n";
                                            cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                                            cin >> choiceThree;
                                            if (choiceThree == 1){
                                                newManager.setSalary(newSalary);
                                                newManager.setUsername(newUsername);
                                                newManager.setPassword(newPassword);

                                                managers.push_back(newManager);
                                                session.addLog("An employee was updated to a manager.\nThe following values were entered:\nSalary: " + to_string(newManager.getSalary()) + "\nUsername: " + newManager.getUsername() + "\nPassword: " + newManager.getPassword() + "\n"); 
                                               
                                                
                                                
                                            }
                                        } while (choiceThree != 1);
                                        cout << "\nSUCCESS -> Employee updated to Manager.\n\n";
                                        // delete old emplyee object in employee list
                                        employees.erase(employees.begin() + indexToDelete);
                                    }
                            }
                            break;
                        case 2:
                            // update employee pay
                            do {
                                cout << "You selected to update an employees pay.\n";
                                cout << "Enter the employee's name that you would like to update." << endl; 
                                cout << "Here is the list of employees names:" << endl; 
                                for (int i = 0; i < employees.size(); i++){
                                    cout << employees[i].getName() << endl; 
                                }
                                cin.ignore();
                                cout << "Enter their name: ";
                                getline(cin, employeeToManagerName);
                                cout << "Are you sure that this is the employee you want to update?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                cin >> employeeToManagerBool;
                            } while(employeeToManagerBool != 1);
                            for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        do {
                                            cout << "\n"; 
                                            cout <<  employeeToManagerName << "'s new pay: $"; 
                                            cin >> newHourlyPayRate;

                                            cout << "\n";
                                            cout << "This is the value you provided for new pay:" << endl; 
                                            cout << "Pay: $" << newHourlyPayRate << endl;
                                            cout << "\n";
                                            cout << "Is this value correct? (Type 1 to confirm OR 2 to deny and re-enter the values): ";
                                            cin >> choiceThree;
                                            if (choiceThree == 1){
                                                employees[i].setHourlyPayRate(newHourlyPayRate);
                                                session.addLog(employeeToManagerName + "'s hourly pay rate was updated.\nThe following value was entered:\nHourly Pay Rate: " + to_string(newHourlyPayRate) + "\n"); 
                                               
                                                
                                                
                                            }
                                        } while (choiceThree != 1);
                                        cout << "\nSUCCESS -> Employee pay updated.\n\n";
                                    }
                            }
                            break;
                        case 3:
                            // change employee shift
                            do {
                                cout << "You selected to update an employees shift.\n";
                                cout << "Enter the employee's name that you would like to update." << endl; 
                                cout << "Here is the list of employees names:" << endl; 
                                for (int i = 0; i < employees.size(); i++){
                                    cout << employees[i].getName() << endl; 
                                }
                                cin.ignore();
                                cout << "Enter their name: ";
                                getline(cin, employeeToManagerName);
                                cout << "Are you sure that this is the employee that you want to update?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                cin >> employeeToManagerBool;
                            } while(employeeToManagerBool != 1);
                            for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        do {
                                            cout << "\n"; 
                                            cout <<  employeeToManagerName << "'s new shift (1 for day OR 2 for night): "; 
                                            cin >> newShift;

                                            cout << "\n";
                                            cout << "This is the value you provided for new shift:" << endl; 
                                            if (newShift == 1){
                                                cout << "Day Shift which is 1st shift" << endl; 
                                            } else{
                                                cout << "Night shift which is 2nd shift" << endl; 
                                            }
                                            cout << "\n";
                                            cout << "Is this shift correct? (Type 1 to confirm OR 2 to deny and re-enter the values): ";
                                            cin >> choiceThree;
                                            if (choiceThree == 1){
                                                employees[i].setShift(newShift);
                                                session.addLog(employeeToManagerName + "'s shift was updated.\nThe following value was entered:\nShift: " + to_string(newShift) + "(1 is Day Shift and 2 is Night Shift)\n"); 
                                                
                                               
                                               
                                            }
                                        } while (choiceThree != 1);
                                        cout << "\nSUCCESS -> Employee shift updated.\n\n";
                                    }
                            }
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid option.\n";
                    }
                } while (updateEmployeeChoice != 4);
                break;
            case 3:
                cout << "You selected to create a new employee.\n";
                cout << "Would you like to create a new production worker or manager? (1 for production worker, 2 for manager): ";
                cin >> employeeChoice;
                if (employeeChoice == 1){
                    do {
                        cout << "\n";
                        cout << "You have selected to create a new production worker." << endl; 
                        cout << "Production Worker Name (John Smith): "; 
                        cin.ignore();
                        getline(cin, name); 
                        cout << "Production Worker Number: ";
                        cin >> number; 
                        cout << "Production Worker Hire Date (11/26/2018): ";
                        cin >> hireDate; 
                        cout << "Production Worker Shift(1 for day or 2 for night): "; 
                        cin >> shift; 
                        cout << "Production Worker Hourly Pay Rate: $";
                        cin >> hourlyPayRate; 

                        cout << "\n";
                        cout << "These are the values you provided:" << endl; 
                        cout << "Name: " << name << endl;
                        cout << "Number: " << number << endl;
                        cout << "Hire Date: " << hireDate << endl;
                        if (shift == 1){
                            cout << "Shift: Day" << endl;
                        } else {
                            cout << "Shift: Night" << endl;
                        }
                        cout << "Hourly Pay Rate: $" << hourlyPayRate << endl;
                        cout << "\n";
                        cout << "Are these values correct? (Type 1 to confirm and add the production worker to the system OR 2 to deny and re-enter the values): ";
                        cin >> choiceTwo;
                        if (choiceTwo == 1){
                            newWorker.setName(name);
                            newWorker.setNumber(number);
                            newWorker.setHireDate(hireDate);
                            newWorker.setShift(shift);
                            newWorker.setHourlyPayRate(hourlyPayRate);

                            employees.push_back(newWorker);
                            session.addLog("A new employee was created.\nThe following value was entered:\nName: " + name + "\nNumber: " + to_string(number) + "\nHire Date: " + hireDate + "\nShift: " + to_string(shift) + "\nHourly Pay Rate: " + to_string(hourlyPayRate) + "\n"); 
                            
                            
                            
                        }
                    } while (choiceTwo != 1);
                    cout << "\nSUCCESS! -> new production worker added.\n" << endl; 
                    
                } else {
                    do {
                        cout << "\n";
                        cout << "You have selected to create a new manager." << endl; 
                        cout << "Manager Salary (60000.00): "; 
                        cin >> salary; 
                        cout << "Manager Username (newuser123 [no spaces allowed]): ";
                        cin >> username; 
                        cout << "Manager Password (password123 [no spaces allowed]): ";
                        cin >> password; 

                        cout << "\n";
                        cout << "These are the values you provided:" << endl; 
                        cout << "Salary: " << salary << endl;
                        cout << "Username: " << username << endl;
                        cout << "Password: " << password << endl;
                        cout << "\n";
                        cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                        cin >> choiceThree;
                        if (choiceThree == 1){
                             newManager.setSalary(salary);
                            newManager.setUsername(username);
                            newManager.setPassword(password);

                            managers.push_back(newManager);
                            session.addLog("A new manager was created.\nThe following values were eneterd:\nSalary: " + to_string(salary) + "\nUsername: " + username + "\nPassword: " + password + "\n");
                            
                            
                            
                        }
                    } while (choiceThree != 1);
                    cout << "\nSUCCESS! -> new manager has been created.\n" << endl; 
                }
                break;
            case 4:
                logouttime = time(nullptr);
                session.setLogoutTime(logouttime);
                session.addLog("Logging out at " + to_string(logouttime) + "\n");
    
                outputFile << session.logSessionInfo();
                
                break; 
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

        cout << endl;

    } while (choice != 4);

    outputFile.close();

    return 0; 
}