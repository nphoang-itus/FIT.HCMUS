#include <iostream>
#include <stdexcept>

class Complex {
private:
    float a, b;
public:
    Complex(float _a, float _b) : a(_a), b(_b) {
        if (a * b < 0) {
            throw std::invalid_argument("Paramenter can't be negative");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Complex c) {
        os << c.a << "+" << c.b << "i";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Complex& c) {
        std::string s;
        getline(is, s, '+');
        c.a = std::stof(s);
        getline(is, s, 'i');
        c.b = std::stof(s);
        return is;
    }
};

int main() {
    try {
        Complex comp(1, -2);
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
    
    return 0;
}