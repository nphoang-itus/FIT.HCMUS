#include "Company.h"

#include <fstream>
#include <sstream>

void Company::addEmployee(std::unique_ptr<Employee> emp) {
    _employeeList.push_back(std::move(emp));
}

void Company::printEmployeeList() {
    std::cout << *this;
}

void Company::printOutstandEmployees() {
    for (const auto& emp : _employeeList) {
        if (emp->checkOutstandingEmployee()) {
            std::cout << *emp << "\n";
        }
    }
}

// nvkt: Tran Van A (Tp Ho Chi Minh) [Dien] <10>
void Company::readListFromFile(const std::string& fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Khong mo duoc file " << fileName << "\n";
        return;
    }

    ifs >> *this;

    ifs.close();
}

std::ostream& operator<<(std::ostream& os, const Company& comp) {
    for (const auto& emp : comp._employeeList) {
        os << *emp << "\n";
    }

    return os;
}

std::istream& operator>>(std::istream& is, Company& comp) {
    std::string line = "";
    // nvkt: Tran Van A (Tp Ho Chi Minh) [Dien] <10>
    while (std::getline(is, line)) {
        std::istringstream issLine(line);
        std::string type = "";
        std::getline(issLine, type, ':');
        std::unique_ptr<Employee> empPtr = nullptr;
        
        if (type == "nvtk") {
            empPtr = std::make_unique<Secretary>();
        } else if (type == "nvkt") {
            empPtr = std::make_unique<Technician>();
        }

        issLine.get(); // Lấy khoảng trắng ở đầu
        if (empPtr) {
            issLine >> *empPtr; // Employee
            comp.addEmployee(std::move(empPtr));
        }

    }

    return is;
}