#include "GeometryManagement.h"
#include "ShapeType.h"
#include <fstream>
#include <iostream>

void GeometryManagement::addGeometry(std::unique_ptr<Geometry> geo) {
    _geometryList.push_back(std::move(geo));
}

void GeometryManagement::readListFromFile(const std::string& fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Không mở được file " << fileName << "\n";
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        auto geometry = GeometryRegistry::getInstance().createGeometry(line);
        if (geometry) {
            addGeometry(std::move(geometry));
        }
    }

    ifs.close();
}

int GeometryManagement::countShapesByType(ShapeType type) const {
    int count = 0;
    for (const auto& geo : _geometryList) {
        if (geo->getShapeType() == type) {
            count++;
        }
    }
    return count;
}

double GeometryManagement::sumOfPerimeter() const {
    double sum = 0.0;
    for (const auto& geo : _geometryList) {
        sum += geo->calculatePerimeter();
    }
    return sum;
}

double GeometryManagement::sumOfArea() const {
    double sum = 0.0;
    for (const auto& geo : _geometryList) {
        sum += geo->calculateArea();
    }
    return sum;
}

std::ostream& operator<<(std::ostream& os, const GeometryManagement& geoMana) {
    os << "So luong hinh cu the moi loai:\n";
    for (int i = 0; i < geoMana.numberOfShapeTypes(); ++i) {
        ShapeType index = static_cast<ShapeType>(i);
        os << getPrefix().at(index) << ": " << geoMana.countShapesByType(index) << "\n";
    }

    os << "Tong chu vi: " << geoMana.sumOfPerimeter() << "\n";
    os << "Tong dien tich: " << geoMana.sumOfArea() << "\n";
    
    return os;
}