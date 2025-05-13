#include "GeometryManagement.h"
#include <iostream>
#include <memory>

int main() {
    GeometryManagement manager;

    manager.readListFromFile("hhp.txt");
    
    std::cout << "Danh sách hình:\n";
    std::cout << manager;
    return 0;
}