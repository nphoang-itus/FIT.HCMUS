#include <iostream>
#include <random>

// Hệ thống cũ
class ITemperatureSensor {
public:
    virtual ~ITemperatureSensor() = default;
    virtual float getTemperatureCelsius() = 0;
};

class CelsiusSensor : public ITemperatureSensor {
private:
    std::mt19937 _gen; // bộ sinh số ngẫu nhiên
    std::uniform_real_distribution<float> _celdius;

public:
    CelsiusSensor() : _gen(std::random_device{}()), _celdius(10.0f, 30.0f) {}

    float getTemperatureCelsius() {
        return _celdius(_gen);
    }
};

class BuildingControlSystem {
public:
    void displayTemperature(ITemperatureSensor& sensor) {
        std::cout << "Current temperature: " << sensor.getTemperatureCelsius() << " C\n";
    }
};

// Hệ thống mới
class FahrenheitThermo {
private:
    std::mt19937 _gen; // bộ sinh số ngẫu nhiên
    std::uniform_real_distribution<float> _fahrenheit;

public:
    FahrenheitThermo() : _gen(std::random_device{}()), _fahrenheit(70.0f, 110.0f) {}

    float getFahrenheitTemp() {
        return _fahrenheit(_gen);
    }
};

class ThermoAdapter : public ITemperatureSensor, public FahrenheitThermo {
public:
    float getTemperatureCelsius() {
        float f = this->getFahrenheitTemp();
        return (f - 32) * 5.0 / 9.0;
    }
};

int main() {
    // Hệ thống cũ
    CelsiusSensor sensor;

    BuildingControlSystem system;
    system.displayTemperature(sensor);

    // Hệ thống mới
    ThermoAdapter adapter;

    BuildingControlSystem system_other;
    system_other.displayTemperature(adapter);

    return 0;
}