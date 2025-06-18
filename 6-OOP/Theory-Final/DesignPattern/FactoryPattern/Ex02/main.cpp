#include <iostream>
#include <string>
#include <vector>

class Shape {
public:
    virtual ~Shape() {}
    virtual void draw() const = 0;
    virtual float getArea() const = 0;
};

class Circle : public Shape {
private:
    float radius;
public:
    void draw() const override {
        std::cout << "Draw circle\n";
    }

    float getArea() const override {
        return 3.14 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    float width;
    float height;
public:
    void draw() const override {
        std::cout << "Draw rectangle\n";
    }

    float getArea() const override {
        return width * height;
    }
};

class Triangle : public Shape {
private:
    float sideA;
    float sideB;
    float sideC;
public:
    void draw() const override {
        std::cout << "Draw triangle\n";
    }

    float getArea() const override {
        return sideA + sideB + sideC; // z cho nhanh
    }
};

class ShapeFactory {
public:
    // Shape* createShape(const std::string& type) const {
    //     if (type == "cir") {
    //         return new Circle;
    //     } else if (type == "rec") {
    //         return new Rectangle;
    //     } else if (type == "tri") {
    //         return new Triangle;
    //     }

    //     return nullptr;
    // };

    virtual ~ShapeFactory() {}
    virtual Shape* createShape() const = 0;

    void describeShape() const {
        std::cout << "Creating a shape: ";
        Shape* shape = createShape();
        if (shape) {
            shape->draw();
        }
        delete shape;
    }
};

class CircleFactory : public ShapeFactory {
public:
    Shape* createShape() const override {
        return new Circle;
    }
};

class RectangleFactory : public ShapeFactory {
public:
    Shape* createShape() const override {
        return new Rectangle;
    }
};

class TriangleFactory : public ShapeFactory {
public:
    Shape* createShape() const override {
        return new Triangle;
    }
};

void clientCode(const ShapeFactory& factory) {
    factory.describeShape();
}

int main() {
    std::vector<std::string> types = {"cir", "tri", "rec"};
    ShapeFactory* factory;

    for (int i = 0; i < types.size(); ++i) {
        if (types[i] == "cir") {
            factory = new CircleFactory;
        } else if (types[i] == "rec") {
            factory = new RectangleFactory;
        } else if (types[i] == "tri") {
            factory = new TriangleFactory;
        }

        if (factory) {
            clientCode(*factory);
            delete factory;
        }
    }
    return 0;
}