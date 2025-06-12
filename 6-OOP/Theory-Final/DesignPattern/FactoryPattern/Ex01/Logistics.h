#ifndef LOGISTICS_H
#define LOGISTICS_H

#include "Delivery.h"

#include <memory>

class Logistics {
public:
    virtual std::shared_ptr<Delivery> createDeliverMethod() = 0;

    void planDelivery(const std::string& address, double distance) {
        std::shared_ptr<Delivery> delivery = createDeliverMethod();
        delivery->deliver(address);
        std::cout << "Giá tiền: " << delivery->calculateCost(distance) << "\n";
    }

    virtual ~Logistics() = default;
};

class RoadLogistics : public Logistics {
public:
    std::shared_ptr<Delivery> createDeliverMethod() override {
        return std::make_shared<RoadDelivery>();
    }
};

class AirLogistics : public Logistics {
public:
    std::shared_ptr<Delivery> createDeliverMethod() override {
        return std::make_shared<AirDelivery>();
    }
};

class SeaLogistics : public Logistics {
public:
    std::shared_ptr<Delivery> createDeliverMethod() override {
        return std::make_shared<SeaDelivery>();
    }
};

#endif