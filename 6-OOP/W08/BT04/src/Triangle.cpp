#include "Triangle.h"
#include <string>
#include <sstream>
#include <iostream>

bool Triangle::_checkValidate() const {
    bool isValid = (_edgeA + _edgeB > _edgeC) && (_edgeA + _edgeC > _edgeB) && (_edgeB + _edgeC > _edgeA);
    if (!isValid) {
        std::cout << "vl";
    }
    return isValid;
}

Triangle::Triangle() : _edgeA(0.0), _edgeB(0.0), _edgeC(0.0) {}

ShapeType Triangle::getShapeType() const {
    return ShapeType::TRIANGLE;
}

Triangle::Triangle(const float& edgeA, const float& edgeB, const float& edgeC)
    : _edgeA(edgeA), _edgeB(edgeB), _edgeC(edgeC) {
    if (!_checkValidate()) {
        std::cerr << "Tam giac khong hop le\n";
        _edgeA = _edgeB = _edgeC = 0;
    }
}

float Triangle::getEdgeA() const {
    return _edgeA;
}

float Triangle::getEdgeB() const {
    return _edgeB;
}

float Triangle::getEdgeC() const {
    return _edgeC;
}

void Triangle::setEdgeA(const float& edgeA) {
    _edgeA = edgeA;
}

void Triangle::setEdgeB(const float& edgeB) {
    _edgeB = edgeB;
}

void Triangle::setEdgeC(const float& edgeC) {
    _edgeC = edgeC;
}

double Triangle::calculatePerimeter() const {
    if (!_checkValidate()) return 0.0;
    return _edgeA + _edgeB + _edgeC;
}

double Triangle::calculateArea() const {
    if (!_checkValidate()) return 0.0;

    double p = (_edgeA + _edgeB + _edgeC) / 2;
    return std::sqrt(p * (p - _edgeA) * (p - _edgeB) * (p - _edgeC));
}

void Triangle::print(std::ostream& os) const {
    os << "htg: " << getEdgeA() << "," << getEdgeB() << "," << getEdgeC();
}

void Triangle::read(std::istream& is) {
    std::string token = "";
    std::getline(is, token, ',');
    setEdgeA(std::stof(token));
    // std::cout << "_edgeA: " << token << "|\n";
    
    std::getline(is,token, ',');
    setEdgeB(std::stof(token));
    // std::cout << "_edgeB: " << token << "|\n";
    
    std::getline(is,token);
    setEdgeC(std::stof(token));
    // std::cout << "_edgeC: " << token << "|\n";
}

std::ostream& operator<<(std::ostream& os, const Triangle& rec) {
    rec.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& rec) {
    rec.read(is);
    return is;
}