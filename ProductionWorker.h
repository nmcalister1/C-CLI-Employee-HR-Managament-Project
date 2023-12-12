#ifndef PRODUCTIONWORKER_H
#define PRODUCTIONWORKER_H
#include "Employee.h"
#include <string>
using namespace std; 

class ProductionWorker : public Employee {
    private: 
        int shift;
        double hourlyPayRate; 
    public: 
        ProductionWorker() : Employee()
            { shift = 0; hourlyPayRate = 0.0; }
        
        ProductionWorker(string nameIn, int numIn, string hireDateIn, int shiftIn, double hourlyPayRateIn) : Employee(nameIn, numIn, hireDateIn)
            { shift = shiftIn; hourlyPayRate = hourlyPayRateIn; }

        void setShift(int s){ shift = s; }
        void setHourlyPayRate(double p){ hourlyPayRate = p; }

        int getShift() const { return shift; }
        double getHourlyPayRate() const {return hourlyPayRate; }
};
#endif