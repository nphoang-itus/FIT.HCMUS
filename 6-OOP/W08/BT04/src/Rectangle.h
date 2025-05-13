#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Geometry.h"

class Rectangle : public Geometry {
private:
    float _width;
    float _height;

public:
    Rectangle();
    Rectangle(const float& width, const float& height);
    
    ShapeType getShapeType() const override;

    float getWidth() const;
    float getHeight() const;
    void setWidth(const float& width);
    void setHeight(const float& height);
    
    double calculatePerimeter() const override;
    double calculateArea() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rec);
    friend std::istream& operator>>(std::istream& is, Rectangle& rec);
};

#endif // RECTANGLE_H