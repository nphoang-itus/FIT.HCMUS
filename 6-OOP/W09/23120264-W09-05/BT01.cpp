#include <iostream>
#include <vector>

class Base {
public:
    virtual ~Base() = default;
    virtual void Print(std::ostream& os) = 0;
    friend std::ostream& operator<<(std::ostream& os, Base& base) {
        base.Print(os);
        return os;        
    }
};

class Derived1 : public Base {
private:
    int _ofD1;
public:
    Derived1(const int& v) {
        _ofD1 = v;
    }

    void Print(std::ostream& os) override {
        os << "D1 - " << _ofD1;
    }
};

class Derived2 : public Base {
private:
    int _ofD2;
public:
    Derived2(const int& v) {
        _ofD2 = v;
    }

    void Print(std::ostream& os) override {
        os << "D 2- " << _ofD2;
    }
};

int main() {
    std::vector<Base*> ds;
    ds.push_back(new Derived1(13));
    ds.push_back(new Derived1(17));
    ds.push_back(new Derived2(24));
    ds.push_back(new Derived2(28));

    for (const auto& x : ds) {
        std::cout << *x << '\n';
    }
    std::cout << "\n";

    for (auto x : ds) {
        delete x;
    }

    return 0;
}