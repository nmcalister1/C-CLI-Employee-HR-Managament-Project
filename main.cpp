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

// checks to see if the user entered an int for that which is supposed to be a string
bool isInteger(const string& s);


int main(){
    // global vectors to store employee objects and manager objects
    vector<ProductionWorker> employees;
    vector<Manager> managers;

    // instantiate a manager
    Manager manager(30.50, "nmcalister", "password123");
    managers.push_back(manager);

    const int DAY_SHIFT = 1;
    const int NIGHT_SHIFT = 2;

    // instantiate employees
    ProductionWorker employee1("Jonny Yur", 1, "11/12/2018", DAY_SHIFT, 25.50);
    ProductionWorker employee2("Kim Tarminsk", 2, "05/14/2016", NIGHT_SHIFT, 24.00);
    ProductionWorker employee3("John Doe", 3, "08/25/2010", NIGHT_SHIFT, 26.70);
    ProductionWorker employee4("Jane Doe", 4, "09/13/2023", DAY_SHIFT, 20.50);
    employees.push_back(employee1);
    employees.push_back(employee2);
    employees.push_back(employee3);
    employees.push_back(employee4);

    // bool to determine whether a user is authorized or not
    bool authUsernameAndPassword = false;
    string checkUsername = "";
    string checkPassword = "";

    // initialize a session
    Session session;

    /*
        !. Allow the user to enter their username and password
        2. Error check and validate the input
    */
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
                // create a new session user
                session.setUser(managers[i].getUsername());
                break; 
            }
        }
        if (!authUsernameAndPassword){
            cout << "\n\n";
            cout << "Your login credentials are not valid, please try again.\n" << endl;
        }
    } while (!authUsernameAndPassword);


    // GLOBAL VARIABLES FOR THE PROGRAM

    // VARIABLES THAT WILL HOLD 1 OR 2 DEPENDING ON THE USERS CHOICE
    int choice; 
    int updateEmployeeChoice; 
    int choiceTwo = 0; 
    int choiceThree = 0;
    int employeeChoice; 

    // INITIALIZE EMPTY PRODUCTIONWORKER AND MANAGER OBJECTS
    ProductionWorker newWorker;
    Manager newManager; 

    string employeeToManagerName; 
    int employeeToManagerBool; 

    /// PRODUCTION WORKER VARIABLES ///
    string name; 
    int number; 
    string hireDate;
    int shift;
    double hourlyPayRate; 

    double newHourlyPayRate;
    int newShift;

    int oldShift; 

    /// MANAGER VARIABLES ///
    float salary; 
    string username; 
    string password; 

    float newSalary; 
    string newUsername; 
    string newPassword; 

    // HOLDS THE INDEX AT WHICH WE NEED TO DELETE AN EMPLOYEE OBJECT IN THE GLOBAL LIST
    int indexToDelete;

    // HOLDS THE SESSION LOGOUT TIME
    time_t logouttime; 

    bool nameBool = false; 

    // OPENS THE LOG.TXT FILE SO THAT WE CAN LOG SESSION DATA TO IT
    ofstream outputFile("log.txt", ios::app);

    /// EXCEPTION HANDLING /// 
    try {
        // THIS CHECKS IF THE FILE IS OPEN
        if (!outputFile.is_open()) {
            // THROW AN ERROR IF THE FILE IS NOT OPEN
            throw runtime_error("This file failed to open.");
        }
    } catch (const exception& e) {
        // PRINT ERROR MESSAGE TO USER
        cerr << "An exception occurred: " << e.what() << endl;
    }
    

    cout << "\n--- Welcome " << checkUsername << " ---\n"<< endl; 

    do {
        // MENU DISPLAY FOR USER
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

        /// SWITCH DEPENDING ON USER CHOICE
        switch (choice) {
            case 1:
                /// VIEW ALL EMPLOYEES ///
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
                /// UPADATE AN EMPLOYEE ///
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
                            /// ASSIGN AN EMPLOYEE TO A MANAGER ///
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

                                /// ERROR CHECKING ///
                                while (!nameBool){
                                    cout << "\nThat is not a valid employee name." << endl; 
                                    cout << "Here is the list of employees names:" << endl; 
                                    for (int i = 0; i < employees.size(); i++){
                                        cout << employees[i].getName() << endl; 
                                    }
                                    cout << "Enter their name: ";
                                    getline(cin, employeeToManagerName);
                                    for (int i = 0; i < employees.size(); i++){
                                        if (employees[i].getName() == employeeToManagerName){
                                            nameBool = true;
                                        }                               
                                    }
                                }
                                
                                cout << "Are you sure that this is the employee that you want to change to become a manager?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                // ERROR CHECKING 
                                while (!(cin >> employeeToManagerBool) || employeeToManagerBool != 1 && employeeToManagerBool != 2) {
                                    cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                    cout << "Are you sure that this is the employee that you want to change to become a manager?: " << employeeToManagerName << " (1 for yes or 2 for no): ";
                                    cin.clear(); 
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while(employeeToManagerBool != 1);
                            for (int i = 0; i < employees.size(); i++){
                                    if (employees[i].getName() == employeeToManagerName){
                                        /// CREATE MANAGER OBJECT AND SAVE IT TO THE GLOBAL LIST ///
                                        indexToDelete = i; 
                                        do {
                                            cout << "\n";
                                            cout << "You have selected to create a new manager out of " << employeeToManagerName << endl; 
                                            cout << "Manager Salary (60000.00): "; 

                                            // ERROR CHECKING 
                                            while (!(cin >> newSalary) || newSalary < 0.0) {
                                                cout << "Invalid salary input. Please enter a valid non-negative float." << endl;
                                                cout << "Manager Salary (60000.00): ";
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }

                                            cin.ignore();
                                            cout << "Manager Username (newuser123 [no spaces allowed]): ";
                                            getline(cin, newUsername);

                                            // ERROR CHECKING 
                                            while (newUsername.find(' ') != string::npos || isInteger(newUsername)) {
                                                cout << "Invalid username input. Spaces are not allowed. Cannot be an integer." << endl;
                                                cout << "Username: ";
                                                getline(cin, newUsername);
                                            }

                                            cout << "Manager Password (password123 [no spaces allowed]): ";
                                            getline(cin, newPassword);

                                            // ERROR CHECKING
                                            while (newPassword.find(' ') != string::npos || isInteger(newPassword)) {
                                                cout << "Invalid password input. Spaces are not allowed. Cannot be an integer." << endl;
                                                cout << "Password: ";
                                                getline(cin, newPassword);
                                            }

                                            // READ THE VALUES BACK TO THE USER //
                                            cout << "\n";
                                            cout << "These are the values you provided:" << endl; 
                                            cout << "Salary: " << newSalary << endl;
                                            cout << "Username: " << newUsername << endl;
                                            cout << "Password: " << newPassword << endl;
                                            cout << "\n";
                                            cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";

                                            // ERROR CHECKING
                                            while (!(cin >> choiceThree) || choiceThree != 1 && choiceThree != 2) {
                                                cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                                cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }

                                            if (choiceThree == 1){
                                                // CREATE A MANAGER OBJECT WITH THE VALUES THE USER ENTERED //
                                                newManager.setSalary(newSalary);
                                                newManager.setUsername(newUsername);
                                                newManager.setPassword(newPassword);

                                                // Convert the float to string with controlled precision //
                                                string salaryString = to_string(newManager.getSalary());
                                                size_t dotPosition = salaryString.find('.');
                                                size_t precision = 2; // Set your desired precision

                                                if (dotPosition != std::string::npos && dotPosition + precision + 1 < salaryString.size()) {
                                                    salaryString.erase(dotPosition + precision + 1);
                                                }

                                                // ADD THE MANAGER TO THE GLOBAL VECTOR
                                                managers.push_back(newManager);
                                                // CREATE A NEW LOG
                                                session.addLog("An employee was updated to a manager.\nThe following values were entered:\nSalary: $" + salaryString + "\nUsername: " + newManager.getUsername() + "\nPassword: " + newManager.getPassword() + "\n");  
                                            }
                                        } while (choiceThree != 1);
                                        cout << "\nSUCCESS -> Employee updated to Manager.\n\n";
                                        // delete old emplyee object in employee list //
                                        employees.erase(employees.begin() + indexToDelete);
                                        break; 
                                    }
                            }
                            break;
                        case 2:
                            /// UPDATE EMPLOYEE PAY ///
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

                                // ERROR CHECKING 
                                while (nameBool != true){
                                    cout << "\nThat is not a valid employee name." << endl; 
                                    cout << "Here is the list of employees names:" << endl; 
                                    for (int i = 0; i < employees.size(); i++){
                                        cout << employees[i].getName() << endl; 
                                    }
                                    
                                    cout << "Enter their name: ";
                                    getline(cin, employeeToManagerName);
                                    for (int i = 0; i < employees.size(); i++){
                                        if (employees[i].getName() == employeeToManagerName){
                                            nameBool = true;
                                        }                               
                                    }
                                }

                                cout << "Are you sure that this is the employee you want to update?: " << employeeToManagerName << " (1 for yes or 2 for no): ";

                                // ERROR CHECKING
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

                                            // ERROR CHECKING
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

                                            // ERROR CHECKING
                                            while (!(cin >> choiceThree) || choiceThree != 1 && choiceThree != 2) {
                                                cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                                cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }

                                            if (choiceThree == 1){
                                                /// UPDATE EMPLOYEE PAY ///
                                                employees[i].setHourlyPayRate(newHourlyPayRate);
                                                // Convert the float to string with controlled precision
                                                string payRateString = to_string(newHourlyPayRate);
                                                size_t dotPosition = payRateString.find('.');
                                                size_t precision = 2; // Set your desired precision

                                                if (dotPosition != std::string::npos && dotPosition + precision + 1 < payRateString.size()) {
                                                    payRateString.erase(dotPosition + precision + 1);
                                                }

                                                // ADD A SESSION LOG
                                                session.addLog(employeeToManagerName + "'s hourly pay rate was updated.\nThe following value was entered:\nHourly Pay Rate: $" + payRateString + "\n");    
                                            }
                                        } while (choiceThree != 1);
                                        cout << "\nSUCCESS -> Employee pay updated.\n\n";
                                        break; 
                                    }
                            }
                            break;
                        case 3:
                            /// UPDATE EMPLOYEE SHIFT ///
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
                                        oldShift = employees[i].getShift();
                                        nameBool = true;
                                        break; 
                                    }                               
                                }

                                // ERROR CHECKING
                                while (!nameBool){
                                    cout << "\nThat is not a valid employee name." << endl; 
                                    cout << "Here is the list of employees names:" << endl; 
                                    for (int i = 0; i < employees.size(); i++){
                                        cout << employees[i].getName() << endl; 
                                    }
                                   
                                    cout << "Enter their name: ";
                                    getline(cin, employeeToManagerName);
                                    for (int i = 0; i < employees.size(); i++){
                                        if (employees[i].getName() == employeeToManagerName){
                                            oldShift = employees[i].getShift();
                                            nameBool = true;
                                            break; 
                                        }                               
                                    }
                                }

                                cout << "Are you sure that this is the employee that you want to update?: " << employeeToManagerName << " (1 for yes or 2 for no): ";

                                // ERROR CHECKING
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
                                            cout << employeeToManagerName << "'s current shift: " << oldShift << endl; 
                                            cout <<  employeeToManagerName << "'s new shift (1 for day OR 2 for night): "; 

                                            // ERROR CHECKING
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

                                            // ERROR CHECKING
                                            while (!(cin >> choiceThree) || choiceThree != 1 && choiceThree != 2) {
                                                cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                                                cout << "Is this shift correct? (Type 1 to confirm OR 2 to deny and re-enter the values): ";
                                                cin.clear(); 
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }

                                            if (choiceThree == 1){
                                                // UPDATE EMPLOYEES SHIFT
                                                employees[i].setShift(newShift);
                                                // ADD NEW LOG
                                                session.addLog(employeeToManagerName + "'s shift was updated.\nThe following value was entered:\nShift: " + to_string(newShift) + "(1 is Day Shift and 2 is Night Shift)\n"); 
                                            }
                                        } while (choiceThree != 1);
                                        cout << "\nSUCCESS -> Employee shift updated.\n\n";
                                        break; 
                                    }
                            }
                            break;
                        default:
                            cout << "Invalid choice. Please enter a valid option.\n";
                    }
                } while (updateEmployeeChoice != 4);
                break;
            case 3:
                /// CREATE A NEW EMPLOYEE (PRODUCTION WORKER OR MANAGER) ///
                cout << "You selected to create a new employee.\n";
                cout << "Would you like to create a new production worker or manager? (1 for production worker, 2 for manager): ";

                // ERROR CHECKING
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

                        // ERROR CHECKING
                        while (isInteger(name)) {
                            cout << "\nInvalid production worker name. Cannot be an integer." << endl;
                            cout << "Production Worker Name (John Smith): "; 
                            getline(cin, name);
                        }

                        cout << "Production Worker Number: ";

                        // ERROR CHECKING
                        while (!(cin >> number)) {
                            cout << "\nInvalid input. Please enter a valid number." << endl;
                            cout << "Production Worker Number: ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        cin.ignore();
                        cout << "Production Worker Hire Date (11/26/2018): ";
                        getline(cin, hireDate);

                        // ERROR CHECKING
                        while (hireDate.find(' ') != string::npos || isInteger(hireDate)) {
                            cout << "\nInvalid hire date input. Spaces are not allowed. Must be in the following format: 11/26/2018" << endl;
                            cout << "Production Worker Hire Date (11/26/2018): ";
                            getline(cin, hireDate);
                        }

                        cout << "Production Worker Shift(1 for day or 2 for night): "; 

                        // ERROR CHECKING
                        while (!(cin >> shift) || shift != 1 && shift != 2) {
                            cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                            cout << "Production Worker Shift(1 for day or 2 for night): "; 
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        cout << "Production Worker Hourly Pay Rate: $";

                        // ERROR CHECKING
                        while (!(cin >> hourlyPayRate) || hourlyPayRate < 0.0) {
                            cout << "\nInvalid pay rate input. Please enter a valid non-negative float." << endl;
                            cout << "Production Worker Hourly Pay Rate: $";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        // READ THE VALUES BACK TO THE USER
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

                        // ERROR CHECKING
                        while (!(cin >> choiceTwo) || choiceTwo != 1 && choiceTwo != 2) {
                            cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                            cout << "Are these values correct? (Type 1 to confirm and add the production worker to the system OR 2 to deny and re-enter the values): ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        if (choiceTwo == 1){
                            // CREATE NEW PRODUCTION WORKER OBJECT
                            newWorker.setName(name);
                            newWorker.setNumber(number);
                            newWorker.setHireDate(hireDate);
                            newWorker.setShift(shift);
                            newWorker.setHourlyPayRate(hourlyPayRate);

                            // ADD TO GLOBAL VECTOR
                            employees.push_back(newWorker);

                            // Convert the float to string with controlled precision
                            string payRateString = to_string(hourlyPayRate);
                            size_t dotPosition = payRateString.find('.');
                            size_t precision = 2; // Set your desired precision

                            if (dotPosition != std::string::npos && dotPosition + precision + 1 < payRateString.size()) {
                                payRateString.erase(dotPosition + precision + 1);
                            }

                            // ADD NEW SESSION LOG
                            session.addLog("A new employee was created.\nThe following value was entered:\nName: " + name + "\nNumber: " + to_string(number) + "\nHire Date: " + hireDate + "\nShift: " + to_string(shift) + "\nHourly Pay Rate: $" + payRateString + "\n"); 
                            
                            
                            
                        }
                    } while (choiceTwo != 1);
                    cout << "\nSUCCESS! -> new production worker added.\n" << endl; 
                    
                } else {
                    do {
                        cout << "\n";
                        cout << "You have selected to create a new manager." << endl; 
                        cout << "Manager Salary (60000.00): "; 

                        // ERROR CHECKING
                        while (!(cin >> salary) || salary < 0.0) {
                            cout << "Invalid salary input. Please enter a valid non-negative float." << endl;
                            cout << "Manager Salary (60000.00): ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        cin.ignore();
                        cout << "Manager Username (newuser123 [no spaces allowed]): ";
                        getline(cin, username);

                        // ERROR CHECKING
                        while (username.find(' ') != string::npos || isInteger(username)) {
                            cout << "Invalid username input. Spaces are not allowed. Cannot be an integer." << endl;
                            cout << "Username: ";
                            getline(cin, username);
                        }

                        cout << "Manager Password (password123 [no spaces allowed]): ";
                        getline(cin, password);

                        // ERROR CHECKING
                        while (password.find(' ') != string::npos || isInteger(password)) {
                            cout << "Invalid password input. Spaces are not allowed. Cannot be an integer." << endl;
                            cout << "Password: ";
                            getline(cin, password);
                        }

                        // READ THE VALUES BACK TO THE USER
                        cout << "\n";
                        cout << "These are the values you provided:" << endl; 
                        cout << "Salary: " << salary << endl;
                        cout << "Username: " << username << endl;
                        cout << "Password: " << password << endl;
                        cout << "\n";
                        cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";

                        // ERROR CHECKING
                        while (!(cin >> choiceThree) || choiceThree != 1 && choiceThree != 2) {
                            cout << "\nInvalid input. Please enter a 1 or a 2." << endl;
                            cout << "Are these values correct? (Type 1 to confirm and add the manager to the system OR 2 to deny and re-enter the values): ";
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        if (choiceThree == 1){
                            // CREATE NEW MANAGER OBJECT
                            newManager.setSalary(salary);
                            newManager.setUsername(username);
                            newManager.setPassword(password);

                            // ADD MANAGER OBJECT TO GLOBAL VECTOR
                            managers.push_back(newManager);

                            // Convert the float to string with controlled precision
                            string salaryString = to_string(salary);
                            size_t dotPosition = salaryString.find('.');
                            size_t precision = 2; // Set your desired precision

                            if (dotPosition != std::string::npos && dotPosition + precision + 1 < salaryString.size()) {
                                salaryString.erase(dotPosition + precision + 1);
                            }

                            // ADD NEW SESSION LOG
                            session.addLog("A new manager was created.\nThe following values were eneterd:\nSalary: $" + salaryString + "\nUsername: " + username + "\nPassword: " + password + "\n");
                        }
                    } while (choiceThree != 1);
                    cout << "\nSUCCESS! -> new manager has been created.\n" << endl; 
                }
                break;
            case 4:
                // STORE LOGOUT TIME
                logouttime = time(nullptr);
                // SET LOGOUT TIME ON SESSION
                session.setLogoutTime(logouttime);
                // ADD FINAL LOG FOR THE LOGOUT TIME
                session.addLog("Logging out at " + session.displayFormattedTime(logouttime) + "\n");
                
                // GET THE SESSION LOGS AND PRINT THEM TO LOG.TXT
                outputFile << session.logSessionInfo();
                break; 
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

        cout << endl;

    } while (choice != 4);

    // CLOSE THE FILESTREAM 
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