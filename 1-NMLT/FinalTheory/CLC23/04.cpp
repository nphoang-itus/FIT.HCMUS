#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

struct Package {
    char id[18], name[16], loc[51], phone[11];
    float weight;
};

bool readFile(char fileName[], Package packs[], int& n) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) return false;
    n = 0;
    char line[100];
    ifs.getline(line, 100);
    while(ifs.getline(line, 100)) {
        Package p;

        char* token = std::strtok(line, "|");
        std::strcpy(p.id, token);

        token = std::strtok(nullptr, "|");
        std::strcpy(p.name, token);

        token = std::strtok(nullptr, "|");
        std::strcpy(p.loc, token);

        token = std::strtok(nullptr, "|");
        std::strcpy(p.phone, token);

        token = std::strtok(nullptr, "|");
        p.weight = std::stof(token);
        packs[n++] = p;
    }
    ifs.close();
    return true;
}

bool checkPackage(Package pack, char deliDist[]) {
    // 220, Nguyen Xi, P26, Binh Thanh
    char* token = std::strtok(pack.loc, ",");
    char dist[51];
    while (token) {
        std::strcpy(dist, token);
        token = std::strtok(nullptr, ",");
    }
    if (std::strstr(dist, deliDist))
        return true;
    return false;
}

void findByDeliveryDist(char inputName[], char outputName[], char deliDist[]) {
    Package packs[100];
    int n = 0;
    if (!readFile(inputName, packs, n)) {
        return;
    }
    
    std::ofstream ofs(outputName);
    ofs << "Ma don hang|Ten nguoi nhan|Dia chi|So dien thoai| Khoi luong\n";

    for (int i = 0; i < n; ++i) {
        if (checkPackage(packs[i], deliDist)) {
            ofs << packs[i].id << "|" << packs[i].name << "|" << packs[i].loc << "|" << packs[i].phone << "|" << packs[i].weight << "\n";
        }
    }

    ofs.close();
}

int main() {
    char input[] = "input.txt";
    char output[] = "output.txt";
    char deli[] = "Binh Thanh";
    findByDeliveryDist(input, output, deli);

    return 0;
}