#include "RightTrapezoid.h"
#include <sstream>
#include <string>

RightTrapezoid::RightTrapezoid() : _topSide(0.0f), _bottomSide(0.0f), _height(0.0f) {}

RightTrapezoid::RightTrapezoid(const float& topSide, const float& bottomSide, const float& height)
    : _topSide(topSide), _bottomSide(bottomSide), _height(height) {}

ShapeType RightTrapezoid::getShapeType() const {
    return ShapeType::RIGHT_TRAPEZOID;
}

float RightTrapezoid::getTopSide() const {
    return _topSide;
}

float RightTrapezoid::getBottomSide() const {
    return _bottomSide;
}

float RightTrapezoid::getHeight() const {
    return _height;
}

void RightTrapezoid::setTopSide(const float& topSide) {
    _topSide = topSide;
}

void RightTrapezoid::setBottomSide(const float& bottomSide) {
    _bottomSide = bottomSide;
}

void RightTrapezoid::setHeight(const float& height) {
    _height = height;
}

float RightTrapezoid::calculateSlantSide() const {
    // Tính cạnh nghiêng bằng định lý Pythagoras
    float diff = fabs(_bottomSide - _topSide);
    return sqrt(diff * diff + _height * _height);
}

double RightTrapezoid::calculatePerimeter() const {
    // Chu vi = đáy lớn + đáy nhỏ + chiều cao + cạnh nghiêng
    return _bottomSide + _topSide + _height + calculateSlantSide();
}

double RightTrapezoid::calculateArea() const {
    // Diện tích = (đáy lớn + đáy nhỏ) * chiều cao / 2
    return (_bottomSide + _topSide) * _height / 2.0;
}

void RightTrapezoid::print(std::ostream& os) const {
    os << "hthv: " << _topSide << "," << _bottomSide
       << "," << _height;
}

void RightTrapezoid::read(std::istream& is) {
    // Đọc theo định dạng: topSide,bottomSide,height
    std::string token;
    
    std::getline(is, token, ',');
    try {
        setTopSide(std::stof(token));
    } catch (const std::exception& e) {
        setTopSide(0.0f);
    }
    
    std::getline(is, token, ',');
    try {
        setBottomSide(std::stof(token));
    } catch (const std::exception& e) {
        setBottomSide(0.0f);
    }
    
    std::getline(is, token);
    try {
        setHeight(std::stof(token));
    } catch (const std::exception& e) {
        setHeight(0.0f);
    }
}

std::ostream& operator<<(std::ostream& os, const RightTrapezoid& trap) {
    trap.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, RightTrapezoid& trap) {
    trap.read(is);
    return is;
}