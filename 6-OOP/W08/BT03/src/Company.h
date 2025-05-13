#ifndef COMPANY_H
#define COMPANY_H

#include "Employee.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

class Company {
private:
    std::vector<std::unique_ptr<Employee>> _employeeList;

public:
    void addEmployee(std::unique_ptr<Employee> emp);
    void printEmployeeList();
    void printOutstandEmployees();
    void readListFromFile(const std::string& fileName);

    friend std::ostream& operator<<(std::ostream& os, const Company& comp);
    friend std::istream& operator>>(std::istream& is, Company& comp);
};

#endif