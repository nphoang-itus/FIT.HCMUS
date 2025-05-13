#include "GeometryFactory.h"
#include <sstream>

std::unique_ptr<Geometry> RectangleFactory::createGeometry(const std::string& data) {
    auto rectangle = std::make_unique<Rectangle>();
    std::istringstream iss(data);
    iss >> *rectangle;
    return rectangle;
}

std::unique_ptr<Geometry> CircleFactory::createGeometry(const std::string& data) {
    auto circle = std::make_unique<Circle>();
    std::istringstream iss(data);
    iss >> *circle;
    return circle;
}

std::unique_ptr<Geometry> TriangleFactory::createGeometry(const std::string& data) {
    auto triangle = std::make_unique<Triangle>();
    std::istringstream iss(data);
    iss >> *triangle;
    return triangle;
}

std::unique_ptr<Geometry> RightTrapezoidFactory::createGeometry(const std::string& data) {
    auto trapezoid = std::make_unique<RightTrapezoid>();
    std::istringstream iss(data);
    iss >> *trapezoid;
    return trapezoid;
}