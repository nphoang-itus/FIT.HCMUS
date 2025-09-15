#include <iostream>
#include <vector>

class Engine {

};

class Passenger {

};

class Car {
private:
    std::vector<Engine*> eList;
    std::vector<Passenger*> passList;

public:
    ~Car() {
        for (auto e : eList) delete e;
    }
};

int main() {
    //
    {
        Car c;
    } // Car bi huy
    //
    return 0;
}