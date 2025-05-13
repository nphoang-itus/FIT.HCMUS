#ifndef CIRCLE_H
#define CIRCLE_H

#include "Geometry.h"

class Circle : public Geometry {
private:
    float _radius;
    static const float PI;

public:
    Circle();
    Circle(const float& radius);

    ShapeType getShapeType() const override;

    float getRadius() const;
    void setRadius(const float& radius);
    
    double calculatePerimeter() const override;
    double calculateArea() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    friend std::ostream& operator<<(std::ostream& os, const Circle& cir);
    friend std::istream& operator>>(std::istream& is, Circle& cir);
};

#endif // CIRCLE_H