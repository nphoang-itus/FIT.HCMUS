#include <iostream>
#include <fstream>
#include <cstring>

#define MAX_LEN 100

struct NhanVien {
    char maSo[MAX_LEN];
    char hoTen[MAX_LEN];
    char gioiTinh[4];
    float mucLuong;
};

void docDanhSachNhanVien(char tenFile[MAX_LEN], NhanVien dsNhanVien[], int& slNhanVien) {
    std::ifstream ifs(tenFile);
    if (!ifs.is_open()) {
        std::cout << "Khong the mo file\n";
        return;
    }

    slNhanVien = 0;
    char line[MAX_LEN];

    while (ifs.getline(line, MAX_LEN)) {
        // nv001-le thi thu-nu-20.5
        NhanVien nv;
        char* token = std::strtok(line, "-");
        
        std::strcpy(nv.maSo, token);
        token = std::strtok(nullptr, "-");

        std::strcpy(nv.hoTen, token);
        token = std::strtok(nullptr, "-");

        std::strcpy(nv.gioiTinh, token);
        token = std::strtok(nullptr, "-");

        char temp[MAX_LEN];
        std::strcpy(temp, token);
        token = std::strtok(nullptr, "-");
        nv.mucLuong = std::stof(temp);

        dsNhanVien[slNhanVien++] = nv;
    }

    ifs.close();
}

void timNhanVien(NhanVien dsNhanVien[], int slNhanVien, char outputName[]) {
    // Tìm số ký tự dài nhất
    int maxLen = 0;
    for (int i = 0; i < slNhanVien; ++i) {
        if (std::strlen(dsNhanVien[i].hoTen) > maxLen) {
            maxLen = std::strlen(dsNhanVien[i].hoTen);
        }
    }

    // Tìm lương cao nhất
    float maxLuong = 0;
    for (int i = 0; i < slNhanVien; ++i) {
        if (dsNhanVien[i].mucLuong > maxLuong) {
            maxLuong = dsNhanVien[i].mucLuong;
        }
    }

    std::ofstream ofs(outputName);
    bool isFound = false;

    for (int i = 0; i < slNhanVien; ++i) {
        if (dsNhanVien[i].mucLuong == maxLuong && std::strlen(dsNhanVien[i].hoTen) == maxLen) {
            isFound = true;
            
            ofs << dsNhanVien[i].maSo << '-';
            ofs << dsNhanVien[i].hoTen << '-';
            ofs << dsNhanVien[i].gioiTinh << '-';
            ofs << dsNhanVien[i].mucLuong;
            ofs << "\n";
        }
    }

    if (!isFound) {
        ofs << "khong ton tai";
    }

    ofs.close();
}

int main() {
    char tenFile[] = "INPUT.txt";
    NhanVien dsNhanVien[100];
    int slNhanVien = 0;

    docDanhSachNhanVien(tenFile, dsNhanVien, slNhanVien);

    for (int i = 0; i < slNhanVien; ++i) {
        std::cout << dsNhanVien[i].maSo << ": " << dsNhanVien[i].hoTen << ", " << dsNhanVien[i].gioiTinh << ", " << dsNhanVien[i].mucLuong << "\n";
    }

    char outputName[] = "OUTPUT.txt";
    timNhanVien(dsNhanVien, slNhanVien, outputName);

    return 0;
}