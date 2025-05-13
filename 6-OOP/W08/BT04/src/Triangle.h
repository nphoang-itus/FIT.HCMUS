#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Geometry.h"

class Triangle : public Geometry {
private:
    float _edgeA;
    float _edgeB;
    float _edgeC;

    bool _checkValidate() const;
public:
    Triangle();
    Triangle(const float& edgeA, const float& edgeB, const float& edgeC);

    ShapeType getShapeType() const override;

    float getEdgeA() const;
    float getEdgeB() const;
    float getEdgeC() const;
    void setEdgeA(const float& edgeA);
    void setEdgeB(const float& edgeB);
    void setEdgeC(const float& edgeB);
    
    double calculatePerimeter() const override;
    double calculateArea() const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    friend std::ostream& operator<<(std::ostream& os, const Triangle& tri);
    friend std::istream& operator>>(std::istream& is, Triangle& tri);
};

#endif //TRIANGLE_H