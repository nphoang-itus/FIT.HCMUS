#include <iostream>
#include <string>
#include <sstream>
#include <format>

class Mobile {
private:
    std::string code;
    std::string name;
    std::string brand;
    std::string manufacturingDate;

public:
    friend std::istream& operator>>(std::istream& is, Mobile& mobile) {
        // nhập theo định dạng có delim '|' ngăn cách giữa các trường
        std::string line = "";
        std::getline(is,line);
        std::istringstream iss(line);
        std::string token = "";
        std::string* feild = &mobile.code;
        while (getline(iss, token, '|')) {
            *feild = token;
            feild++;
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Mobile& mobile) {
        os << std::format(
            "code=\"{}\",name=\"{}\",brand=\"{}\",manufacturingDate=\"{}\"",
            mobile.code, mobile.name, mobile.brand, mobile.manufacturingDate
        );

        return os;
    }

    int compareMobileByManufacturingDate(const Mobile& other) const {
        // so sánh this với other: if == return 0, if < return -1, if > return 1
        if (this->manufacturingDate == other.manufacturingDate)
            return 0;
        else if (this->manufacturingDate < other.manufacturingDate)
            return -1;
        return 1;
    }
};

int main() {
    std::string line = "IOS13041102|Iphone 23 pro max|Apple|03/07/2025";
    std::istringstream iss(line);
    Mobile mobile;
    iss >> mobile;
    std::cout << mobile << "\n";
    return 0;
}