#ifndef MANAGER_H
#define MANAGER_H
#include "Employee.h"
#include "ProductionWorker.h"
#include <string>
#include <vector>
using namespace std; 

class Manager{
    private: 
        float salary; 
        string username; 
        string password; 
        vector<ProductionWorker> employees; 
    public: 
        Manager()
            : salary(0.0), username(""), password(""){}
        
        Manager(float salaryIn, string usernameIn, string passwordIn) 
            : salary(salaryIn), username(usernameIn), password(passwordIn) {}

        void setSalary(float s){ salary = s; }
        void setUsername(string u){ username = u; }
        void setPassword(string p){ password = p; }
        void addEmployee(ProductionWorker employee) {
            employees.push_back(employee);
        }
        
        float getSalary() const { return salary; }
        string getUsername() const { return username; }
        string getPassword() const { return password; }
        string getEmployees() const {
            string employeeNames;
            for (const ProductionWorker& employee : employees) {
                employeeNames += employee.getName() + " " + to_string(employee.getNumber()) + " " +  employee.getHireDate() + " " +  to_string(employee.getShift()) + " " +  to_string(employee.getHourlyPayRate()) + "\n";
            }
            return employeeNames;
        }
};
#endif