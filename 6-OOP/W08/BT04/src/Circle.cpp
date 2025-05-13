#include "Circle.h"

const float Circle::PI = 3.1415;

Circle::Circle() : _radius(0.0) {}

Circle::Circle(const float& radius) : _radius(radius) {}

ShapeType Circle::getShapeType() const {
    return ShapeType::CIRCLE;
}

float Circle::getRadius() const {
    return _radius;
}

void Circle::setRadius(const float& radius) {
    _radius = radius;
}

double Circle::calculatePerimeter() const {
    return 2 * Circle::PI * _radius;
}

double Circle::calculateArea() const {
    return Circle::PI * _radius * _radius;
}

void Circle::print(std::ostream& os) const {
    os << "htr: " << _radius;
}

void Circle::read(std::istream& is) {
    is >> _radius;
}

std::ostream& operator<<(std::ostream& os, const Circle& cir) {
    cir.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Circle& cir) {
    cir.read(is);
    return is;
}