#include "Rectangle.h"
#include <sstream>
#include <string>

Rectangle::Rectangle() : _width(0.0), _height(0.0) {}

Rectangle::Rectangle(const float& width, const float& height)
    : _width(width), _height(height) {}

ShapeType Rectangle::getShapeType() const {
    return ShapeType::RECTANGLE;
}

float Rectangle::getWidth() const {
    return _width;
}

float Rectangle::getHeight() const {
    return _height;
}

void Rectangle::setWidth(const float& width) {
    _width = width;
}

void Rectangle::setHeight(const float& height) {
    _height = height;
}

double Rectangle::calculatePerimeter() const {
    return 2.0 * (_width + _height);
}

double Rectangle::calculateArea() const {
    return _width * _height;
}

void Rectangle::print(std::ostream& os) const {
    os << "hcn: " << getHeight() << "," << getWidth();
}

void Rectangle::read(std::istream& is) {
    std::string token = "";
    std::getline(is, token, ',');
    setHeight(std::stof(token));
    
    std::getline(is, token);
    setWidth(std::stof(token));
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rec) {
    rec.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& rec) {
    rec.read(is);
    return is;
}