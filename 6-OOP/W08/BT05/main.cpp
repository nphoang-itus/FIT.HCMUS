#include <iostream>
#include <vector>
#include "Hinh.h"

int main() {
    std::vector<Hinh*> dsHinh;

    dsHinh.push_back(new HinhTron(3.5));
    dsHinh.push_back(new HinhTamGiacDeu(8.5));
    dsHinh.push_back(new HinhChuNhat(3.7, 1.9));
    dsHinh.push_back(new HinhVuong(4.1));
    dsHinh.push_back(new HinhCau(13.5));
    dsHinh.push_back(new HinhLapPhuong(2.9));
    dsHinh.push_back(new HinhHop(1.2, 3.7, 6.3));
    dsHinh.push_back(new HinhTru(6.1, 4.9));
    dsHinh.push_back(new HinhNon(8.7, 3.2));

    // <ten hinh> [P hoac Sxq = xx, S hoac V = ]
    for (int i = 0; i < dsHinh.size(); ++i) {
        std::cout << *dsHinh[i] << "\n";
    }

    std::cout << "\n";

    for (Hinh* hinh : dsHinh) {
        if (hinh) {
            delete hinh;
        }
    }

    return 0;
}