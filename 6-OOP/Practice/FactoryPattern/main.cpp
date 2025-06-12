#include <iostream>
#include <memory>
#include <cmath>

const double PI = 3.14159265359;

// Product Interface
class IShape {
public:
    virtual ~IShape() {}
    virtual void draw() const = 0;
    virtual double getArea() const = 0;
};

// Concrete Products
class Circle : public IShape {
private:
    double _radius;

public:
    Circle(double radius) : _radius(radius) {}

    void draw() const override {
        std::cout << "Drawing a Circle with radius " << _radius << std::endl;
    }

    double getArea() const override {
        return PI * _radius * _radius;
    }
};

class Rectangle : public IShape {
private:
    double _length;
    double _width;

public:
    Rectangle(double length, double width) : _length(length), _width(width) {}

    void draw() const override {
        std::cout << "Drawing a Rectangle with length " << _length 
                  << " and width " << _width << std::endl;
    }

    double getArea() const override {
        return _length * _width;
    }
};

class Triangle : public IShape {
private:
    double _a, _b, _c; // 3 cạnh

public:
    Triangle(double a, double b, double c) : _a(a), _b(b), _c(c) {}

    void draw() const override {
        std::cout << "Drawing a Triangle with sides " << _a 
                  << ", " << _b << ", " << _c << std::endl;
    }

    double getArea() const override {
        // Sử dụng công thức Heron
        double s = (_a + _b + _c) / 2.0;
        return sqrt(s * (s - _a) * (s - _b) * (s - _c));
    }
};

// Creator (Abstract Factory)
class ShapeFactory {
public:
    virtual ~ShapeFactory() {}
    
    // Factory Method - pure virtual
    virtual std::unique_ptr<IShape> createShape() const = 0;
    
    // Template Method sử dụng Factory Method
    void processShape() const {
        auto shape = createShape();
        shape->draw();
        std::cout << "Area: " << shape->getArea() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
};

// Concrete Creators
class CircleFactory : public ShapeFactory {
private:
    double _radius;

public:
    CircleFactory(double radius) : _radius(radius) {}

    std::unique_ptr<IShape> createShape() const override {
        return std::make_unique<Circle>(_radius);
    }
};

class RectangleFactory : public ShapeFactory {
private:
    double _length;
    double _width;

public:
    RectangleFactory(double length, double width) : _length(length), _width(width) {}

    std::unique_ptr<IShape> createShape() const override {
        return std::make_unique<Rectangle>(_length, _width);
    }
};

class TriangleFactory : public ShapeFactory {
private:
    double _a, _b, _c;

public:
    TriangleFactory(double a, double b, double c) : _a(a), _b(b), _c(c) {}

    std::unique_ptr<IShape> createShape() const override {
        return std::make_unique<Triangle>(_a, _b, _c);
    }
};

int main() {
    std::cout << "=== Factory Method Pattern Demo ===\n" << std::endl;

    // Tạo các factory instances với parameters
    CircleFactory circleFactory(5.0);
    RectangleFactory rectangleFactory(4.0, 6.0);
    TriangleFactory triangleFactory(3.0, 4.0, 5.0);

    std::cout << "Using processShape() method:" << std::endl;
    
    // Sử dụng processShape() - Template Method
    circleFactory.processShape();
    rectangleFactory.processShape();
    triangleFactory.processShape();

    std::cout << "\nUsing createShape() directly:" << std::endl;
    
    // Sử dụng createShape() trực tiếp
    auto circle = circleFactory.createShape();
    auto rectangle = rectangleFactory.createShape();
    auto triangle = triangleFactory.createShape();

    circle->draw();
    std::cout << "Circle area: " << circle->getArea() << std::endl;

    rectangle->draw();
    std::cout << "Rectangle area: " << rectangle->getArea() << std::endl;

    triangle->draw();
    std::cout << "Triangle area: " << triangle->getArea() << std::endl;

    std::cout << "\n=== Testing different parameters ===" << std::endl;
    
    // Test với các parameters khác
    CircleFactory smallCircle(2.5);
    RectangleFactory square(3.0, 3.0);
    TriangleFactory rightTriangle(6.0, 8.0, 10.0);

    smallCircle.processShape();
    square.processShape();
    rightTriangle.processShape();

    return 0;
}