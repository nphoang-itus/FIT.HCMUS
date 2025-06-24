#include <iostream>
#include <fstream>

int main() {
    std::ifstream ifs("input.txt");
    int n;
    std::string s;
    ifs >> n;
    ifs.ignore();
    ifs >> s;
    std::cout << n << " " << s << "\n";

    return 0;
}