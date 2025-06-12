#include <iostream>
#include "Delivery.h"
#include "Logistics.h"

int main() {
    // Road
    std::shared_ptr<Logistics> log = std::make_shared<RoadLogistics>();
    log->planDelivery("Ho Chi Minh", 123);

    return 0;
}