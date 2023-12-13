#include <iostream>
#include "Employee.h"
#include "ProductionWorker.h"
#include "Manager.h"
#include "Session.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <limits>
#include <cctype>
using namespace std; 

bool isInteger(const string& s);


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
        getline(cin, checkUsername);
        while (checkUsername.find(' ') != string::npos || isInteger(checkUsername)) {
            cout << "Invalid username input. Spaces are not allowed. Cannot be an integer." << endl;
            cout << "Username: ";
            getline(cin, checkUsername);
        }
        
        cout << "Password: "; 
        getline(cin, checkPassword);
        while (checkPassword.find(' ') != string::npos || isInteger(checkPassword)) {
            cout << "Invalid password input. Spaces are not allowed. Cannot be an integer." << endl;
            cout << "Password: ";
            getline(cin, checkPassword);
        }

        authUsernameAndPassword = false; 

        for (int i = 0; i < managers.size(); i++){
            if (managers[i].getUsername() == checkUsername && managers[i].getPassword() == checkPassword){
                authUsernameAndPassword = true;
                session.setUser(managers[i].getUsername());
                break; 
            }
        }
        if (!authUsernameAndPassword){
            cout << "\n\n";
            cout << "Your login credentials are not valid, please try again.\n" << endl;
        }
    } while (!authUsernameAndPassword);

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

    bool nameBool = false; 

    ofstream outputFile("log.txt");
    

    cout << "\n--- Welcome " << checkUsername << " ---\n"<< endl; 

    do {
        cout << "Menu:\n";
        cout << "1. View Current Employees\n";
        cout << "2. Update an Employee\n";
        cout << "3. Create New Employee\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";
        if (cin >> choice){
            cout << "\n";
        } else {

            // Input was not an integer
            cout << "Invalid input. Please enter an integer. Press ENTER to go back to menu." << endl;

            // Clear the input stream to handle the invalid input
            cin.clear();

            // Discard the invalid input from the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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
                    if (cin >> updateEmployeeChoice){
                        cout << "\n";
                    } else {
                        // Input was not an integer
                        cout << "Invalid input. Please enter an integer. Press ENTER to go back to menu." << endl;

                        // Clear the input stream to handle the invalid input
                        cin.clear();

                        // Discard the invalid input from the input buffer
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }

                    switch(updateEmployeeChoice){
                        case 1:
                            // assign employee to manager
                            
                            do {
                                nameBool = false; 
                                cout << "\nYou selected to assign an employee to a manager.\n";
                                cout << "Enter the employee's name that you would like to change to a manager." << endl; 
                                cout << "Here is the list of employees names:" << endl; 
                                for (int i = 0; i < employees.size(); i++){
                                    cout << employees[i].getName() << endl; 
                                }
                                cin.ignore();
                                cout << "Enter their name: ";
                                getline(cin, employeeToManagerName);
                                for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        nameBool = true;
                                    }                               
                                }
                                while (nameBool != true){
                                    cout << "\nThat is not a valid employee name." << endl; 
                                    cout << "Here is the list of employees names:" << endl; 
                                    for (int i = 0; i < employees.size(); i++){
                                        cout << employees[i].getName() << endl; 
                                    }
                                    //cin.ignore();
                                    cout << "Enter their name: ";
                                    getline(cin, employeeToManagerName);
                                    for (int i = 0; i < employees.size(); i++){
                                        if (employees[i].getName() == employeeToManagerName){
                                            nameBool = true;
                                        }                               
                                    }
                                }
                                
                                cout << "Are you sure that this is the employee that you want to change to become a manager?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                while (!(cin >> employeeToManagerBool) || employeeToManagerBool != 1 && employeeToManagerBool != 2) {
                                    cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                    cout << "Are you sure that this is the employee that you want to change to become a manager?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                    cin.clear(); 
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while(employeeToManagerBool != 1);
                            for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        // create manager object
                                        indexToDelete = i; 
                                        do {
                                            cout << "\n";
                                            cout << "You have selected to create a new manager out of " << employeeToManagerName << endl; 
                                            cout << "Manager Salary (60000.00): "; 
                                            while (!(cin >> newSalary) || newSalary < 0.0) {
                                                cout << "Invalid salary input. Please enter a valid non-negative float." << endl;
                                                cout << "Manager Salary (60000.00): ";
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }
                                            cin.ignore();
                                            cout << "Manager Username (newuser123 [no spaces allowed]): ";
                                            getline(cin, newUsername);
                                            while (newUsername.find(' ') != string::npos || isInteger(newUsername)) {
                                                cout << "Invalid username input. Spaces are not allowed. Cannot be an integer." << endl;
                                                cout << "Username: ";
                                                getline(cin, newUsername);
                                            }
                                            cout << "Manager Password (password123 [no spaces allowed]): ";
                                            getline(cin, newPassword);
                                            while (newPassword.find(' ') != string::npos || isInteger(newPassword)) {
                                                cout << "Invalid password input. Spaces are not allowed. Cannot be an integer." << endl;
                                                cout << "Password: ";
                                                getline(cin, newPassword);
                                            }

                                            cout << "\n";
                                            cout << "These are the values you provided:" << endl; 
                                            cout << "Salary: " << newSalary << endl;
                                            cout << "Username: " << newUsername << endl;
                                            cout << "Password: " << newPassword << endl;
                                            cout << "\n";
                                            cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                                            while (!(cin >> choiceThree) || choiceThree != 1 && choiceThree != 2) {
                                                cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                                cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }
                                            if (choiceThree == 1){
                                                newManager.setSalary(newSalary);
                                                newManager.setUsername(newUsername);
                                                newManager.setPassword(newPassword);

                                                // Convert the float to string with controlled precision
                                                string salaryString = to_string(newManager.getSalary());
                                                size_t dotPosition = salaryString.find('.');
                                                size_t precision = 2; // Set your desired precision

                                                if (dotPosition != std::string::npos && dotPosition + precision + 1 < salaryString.size()) {
                                                    salaryString.erase(dotPosition + precision + 1);
                                                }

                                                managers.push_back(newManager);
                                                session.addLog("An employee was updated to a manager.\nThe following values were entered:\nSalary: $" + salaryString + "\nUsername: " + newManager.getUsername() + "\nPassword: " + newManager.getPassword() + "\n"); 
                                               
                                                
                                                
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
                                nameBool = false;
                                cout << "You selected to update an employees pay.\n";
                                cout << "Enter the employee's name that you would like to update." << endl; 
                                cout << "Here is the list of employees names:" << endl; 
                                for (int i = 0; i < employees.size(); i++){
                                    cout << employees[i].getName() << endl; 
                                }
                                cin.ignore();
                                cout << "Enter their name: ";
                                getline(cin, employeeToManagerName);
                                for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        nameBool = true;
                                        break; 
                                    }                               
                                }
                                while (nameBool != true){
                                    cout << "\nThat is not a valid employee name." << endl; 
                                    cout << "Here is the list of employees names:" << endl; 
                                    for (int i = 0; i < employees.size(); i++){
                                        cout << employees[i].getName() << endl; 
                                    }
                                    //cin.ignore();
                                    cout << "Enter their name: ";
                                    getline(cin, employeeToManagerName);
                                    for (int i = 0; i < employees.size(); i++){
                                        if (employees[i].getName() == employeeToManagerName){
                                            nameBool = true;
                                        }                               
                                    }
                                }
                                cout << "Are you sure that this is the employee you want to update?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                while (!(cin >> employeeToManagerBool) || employeeToManagerBool != 1 && employeeToManagerBool != 2) {
                                    cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                    cout << "Are you sure that this is the employee you want to update?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                    cin.clear(); 
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while(employeeToManagerBool != 1);
                            for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        do {
                                            cout << "\n"; 
                                            cout <<  employeeToManagerName << "'s new pay: $"; 
                                            while (!(cin >> newHourlyPayRate) || newHourlyPayRate < 0.0) {
                                                cout << "\nInvalid pay rate input. Please enter a valid non-negative float." << endl;
                                                cout <<  employeeToManagerName << "'s new pay: $"; 
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }

                                            cout << "\n";
                                            cout << "This is the value you provided for new pay:" << endl; 
                                            cout << "Pay: $" << newHourlyPayRate << endl;
                                            cout << "\n";
                                            cout << "Is this value correct? (Type 1 to confirm OR 2 to deny and re-enter the values): ";
                                            while (!(cin >> choiceThree) || choiceThree != 1 && choiceThree != 2) {
                                                cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                                cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }
                                            if (choiceThree == 1){
                                                employees[i].setHourlyPayRate(newHourlyPayRate);
                                                // Convert the float to string with controlled precision
                                                string payRateString = to_string(newHourlyPayRate);
                                                size_t dotPosition = payRateString.find('.');
                                                size_t precision = 2; // Set your desired precision

                                                if (dotPosition != std::string::npos && dotPosition + precision + 1 < payRateString.size()) {
                                                    payRateString.erase(dotPosition + precision + 1);
                                                }
                                                session.addLog(employeeToManagerName + "'s hourly pay rate was updated.\nThe following value was entered:\nHourly Pay Rate: $" + payRateString + "\n"); 
                                               
                                                
                                                
                                            }
                                        } while (choiceThree != 1);
                                        cout << "\nSUCCESS -> Employee pay updated.\n\n";
                                    }
                            }
                            break;
                        case 3:
                            // change employee shift
                            do {
                                nameBool = false; 
                                cout << "You selected to update an employees shift.\n";
                                cout << "Enter the employee's name that you would like to update." << endl; 
                                cout << "Here is the list of employees names:" << endl; 
                                for (int i = 0; i < employees.size(); i++){
                                    cout << employees[i].getName() << endl; 
                                }
                                cin.ignore();
                                cout << "Enter their name: ";
                                getline(cin, employeeToManagerName);
                                for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        nameBool = true;
                                        break; 
                                    }                               
                                }
                                while (nameBool != true){
                                    cout << "\nThat is not a valid employee name." << endl; 
                                    cout << "Here is the list of employees names:" << endl; 
                                    for (int i = 0; i < employees.size(); i++){
                                        cout << employees[i].getName() << endl; 
                                    }
                                    //cin.ignore();
                                    cout << "Enter their name: ";
                                    getline(cin, employeeToManagerName);
                                    for (int i = 0; i < employees.size(); i++){
                                        if (employees[i].getName() == employeeToManagerName){
                                            nameBool = true;
                                        }                               
                                    }
                                }
                                cout << "Are you sure that this is the employee that you want to update?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                while (!(cin >> employeeToManagerBool) || employeeToManagerBool != 1 && employeeToManagerBool != 2) {
                                    cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                    cout << "Are you sure that this is the employee that you want to update?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                    cin.clear(); 
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while(employeeToManagerBool != 1);
                            for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        do {
                                            cout << "\n"; 
                                            cout <<  employeeToManagerName << "'s new shift (1 for day OR 2 for night): "; 
                                            while (!(cin >> newShift) || newShift != 1 && newShift != 2) {
                                                cout << "\nInvalid shift input. Please enter a 1 or a 2." << endl;
                                                cout <<  employeeToManagerName << "'s new shift (1 for day OR 2 for night): "; 
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }

                                            cout << "\n";
                                            cout << "This is the value you provided for new shift:" << endl; 
                                            if (newShift == 1){
                                                cout << "Day Shift which is 1st shift" << endl; 
                                            } else{
                                                cout << "Night shift which is 2nd shift" << endl; 
                                            }
                                            cout << "\n";
                                            cout << "Is this shift correct? (Type 1 to confirm OR 2 to deny and re-enter the values): ";
                                            while (!(cin >> choiceThree) || choiceThree != 1 && choiceThree != 2) {
                                                cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                                cout << "Is this shift correct? (Type 1 to confirm OR 2 to deny and re-enter the values): ";
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }
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
                while (!(cin >> employeeChoice) || employeeChoice != 1 && employeeChoice != 2) {
                    cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                    cout << "Would you like to create a new production worker or manager? (1 for production worker, 2 for manager): ";
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (employeeChoice == 1){
                    do {
                        cout << "\n";
                        cout << "You have selected to create a new production worker." << endl; 
                        cout << "Production Worker Name (John Smith): "; 
                        cin.ignore();
                        getline(cin, name); 
                        while (isInteger(name)) {
                            cout << "\nInvalid production worker name. Cannot be an integer." << endl;
                            cout << "Production Worker Name (John Smith): "; 
                            getline(cin, name);
                        }
                        cout << "Production Worker Number: ";
                        while (!(cin >> number)) {
                            cout << "\nInvalid input. Please enter a valid number." << endl;
                            cout << "Production Worker Number: ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore();
                        cout << "Production Worker Hire Date (11/26/2018): ";
                        getline(cin, hireDate);
                        while (hireDate.find(' ') != string::npos || isInteger(hireDate)) {
                            cout << "\nInvalid hire date input. Spaces are not allowed. Must be in the following format: 11/26/2018" << endl;
                            cout << "Production Worker Hire Date (11/26/2018): ";
                            getline(cin, hireDate);
                        }
                        cout << "Production Worker Shift(1 for day or 2 for night): "; 
                        while (!(cin >> shift) || shift != 1 && shift != 2) {
                            cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                            cout << "Production Worker Shift(1 for day or 2 for night): "; 
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cout << "Production Worker Hourly Pay Rate: $";
                        while (!(cin >> hourlyPayRate) || hourlyPayRate < 0.0) {
                            cout << "\nInvalid pay rate input. Please enter a valid non-negative float." << endl;
                            cout << "Production Worker Hourly Pay Rate: $";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

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
                        while (!(cin >> choiceTwo) || choiceTwo != 1 && choiceTwo != 2) {
                            cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                            cout << "Are these values correct? (Type 1 to confirm and add the production worker to the system OR 2 to deny and re-enter the values): ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (choiceTwo == 1){
                            newWorker.setName(name);
                            newWorker.setNumber(number);
                            newWorker.setHireDate(hireDate);
                            newWorker.setShift(shift);
                            newWorker.setHourlyPayRate(hourlyPayRate);

                            employees.push_back(newWorker);
                            // Convert the float to string with controlled precision
                            string payRateString = to_string(hourlyPayRate);
                            size_t dotPosition = payRateString.find('.');
                            size_t precision = 2; // Set your desired precision

                            if (dotPosition != std::string::npos && dotPosition + precision + 1 < payRateString.size()) {
                                payRateString.erase(dotPosition + precision + 1);
                            }
                            session.addLog("A new employee was created.\nThe following value was entered:\nName: " + name + "\nNumber: " + to_string(number) + "\nHire Date: " + hireDate + "\nShift: " + to_string(shift) + "\nHourly Pay Rate: $" + payRateString + "\n"); 
                            
                            
                            
                        }
                    } while (choiceTwo != 1);
                    cout << "\nSUCCESS! -> new production worker added.\n" << endl; 
                    
                } else {
                    do {
                        cout << "\n";
                        cout << "You have selected to create a new manager." << endl; 
                        cout << "Manager Salary (60000.00): "; 
                        while (!(cin >> salary) || salary < 0.0) {
                            cout << "Invalid salary input. Please enter a valid non-negative float." << endl;
                            cout << "Manager Salary (60000.00): ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore();
                        cout << "Manager Username (newuser123 [no spaces allowed]): ";
                        getline(cin, username);
                        while (username.find(' ') != string::npos || isInteger(username)) {
                            cout << "Invalid username input. Spaces are not allowed. Cannot be an integer." << endl;
                            cout << "Username: ";
                            getline(cin, username);
                        }
                        cout << "Manager Password (password123 [no spaces allowed]): ";
                        getline(cin, password);
                        while (password.find(' ') != string::npos || isInteger(password)) {
                            cout << "Invalid password input. Spaces are not allowed. Cannot be an integer." << endl;
                            cout << "Password: ";
                            getline(cin, password);
                        }

                        cout << "\n";
                        cout << "These are the values you provided:" << endl; 
                        cout << "Salary: " << salary << endl;
                        cout << "Username: " << username << endl;
                        cout << "Password: " << password << endl;
                        cout << "\n";
                        cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                        while (!(cin >> choiceThree) || choiceThree != 1 && choiceThree != 2) {
                            cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                            cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (choiceThree == 1){
                            newManager.setSalary(salary);
                            newManager.setUsername(username);
                            newManager.setPassword(password);


                            managers.push_back(newManager);
                            // Convert the float to string with controlled precision
                            string salaryString = to_string(salary);
                            size_t dotPosition = salaryString.find('.');
                            size_t precision = 2; // Set your desired precision

                            if (dotPosition != std::string::npos && dotPosition + precision + 1 < salaryString.size()) {
                                salaryString.erase(dotPosition + precision + 1);
                            }
                            session.addLog("A new manager was created.\nThe following values were eneterd:\nSalary: $" + salaryString + "\nUsername: " + username + "\nPassword: " + password + "\n");
                            
                            
                            
                        }
                    } while (choiceThree != 1);
                    cout << "\nSUCCESS! -> new manager has been created.\n" << endl; 
                }
                break;
            case 4:
                logouttime = time(nullptr);
                session.setLogoutTime(logouttime);
                session.addLog("Logging out at " + session.displayFormattedTime(logouttime) + "\n");
                
    
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

bool isInteger(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}