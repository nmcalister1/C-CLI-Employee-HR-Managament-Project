#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
using namespace std; 

class Employee{
    private: 
        string name; 
        int number; 
        string hireDate; 

    public: 
        Employee()
            { name = ""; number = 0; hireDate = ""; }
        
        Employee(string nameIn, int numIn, string hireDateIn) 
            : name(nameIn), number(numIn), hireDate(hireDateIn) {}

        void setName(string n){ name = n; }
        void setNumber(int n){ number = n; }
        void setHireDate(string d){ hireDate = d; }
        
        string getName() const { return name; }
        int getNumber() const { return number; }
        string getHireDate() const { return hireDate; }

        
};
#endif