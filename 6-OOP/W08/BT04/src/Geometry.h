#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "ShapeType.h"
#include <iostream>

class Geometry {
public:
    virtual ~Geometry() = default; // Thêm virtual destructor: nếu có tạo con trỏ thì nó sẽ đa hình đến đúng lại để delete
    
    virtual ShapeType getShapeType() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual double calculateArea() const = 0;
    
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
};

#endif // GEOMETRY_H