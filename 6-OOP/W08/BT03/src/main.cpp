#include "Company.h"
#include "Employee.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    Company comp;
    std::string fileName = "input.txt";
    comp.readListFromFile(fileName);

    std::cout << "Danh sach nhan vien:\n";
    std::cout << comp;

    std::cout << "\n\nDanh sach nhan vien xuat sac\n";
    comp.printOutstandEmployees();

    return 0;
}