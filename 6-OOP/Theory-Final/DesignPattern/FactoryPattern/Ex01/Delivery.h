#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <iostream>

class Delivery {
public:
    virtual void deliver(const std::string& address) = 0;
    virtual double calculateCost(double distance) = 0;
    virtual ~Delivery() = default;
};

class RoadDelivery : public Delivery {
public:
    void deliver(const std::string& address) override {
        std::cout << "Đang giao bằng đường bộ đến địa chỉ " << address << "\n";
    }

    double calculateCost(double distance) override {
        return 5.0 + 0.5 * distance;
    }
};

class AirDelivery : public Delivery {
public:
    void deliver(const std::string& address) override {
        std::cout << "Đang giao bằng đường hàng không đến địa chỉ " << address << "\n";
    }

    double calculateCost(double distance) override {
        return 50.0 + 2 * distance;
    }    
};

class SeaDelivery : public Delivery {
public:
    void deliver(const std::string& address) override {
        std::cout << "Đang giao bằng đường thuỷ đến địa chỉ " << address << "\n";
    }

    double calculateCost(double distance) override {
        return 10.0 + 0.1 * distance;
    }
};

#endif