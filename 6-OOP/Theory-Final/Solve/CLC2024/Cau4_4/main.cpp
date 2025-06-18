#include <iostream>
#include <string>
#include <vector>

enum class DrawType {
    Solid,
    Hollow
};

struct Info {
    std::string shapeType;
    DrawType drawType;
    char character;
};

class IShape {
public:
    virtual ~IShape() = default;
    virtual std::string type() = 0;
};

class Rectangle : public IShape {
private:
    float width;
    float height;
public:
    Rectangle(float a, float b) : width(a), height(b) {};
    std::string type() override {
        return "Rectangle";
    }
};

class Square : public IShape {
private:
    float side;
public:
    Square(float a) : side(a) {};
    std::string type() override {
        return "Square";
    }
};

class IDrawer {
public:
    virtual ~IDrawer() = default;
    virtual std::string draw(Info* info) = 0;
};

class SolidDrawer : public IDrawer {
public:
    std::string draw(Info* info) override {
        return "Draw " + info->shapeType + " with solid type and character '" + info->character + "'\n";
    }
};

class HollowDrawer : public IDrawer {
public:
    std::string draw(Info* info) override {
        return "Draw " + info->shapeType + " with hollow type and character '" + info->character + "'\n";
    }
};

class DrawFactory {
public:
    IDrawer* create(DrawType type) {
        if (type == DrawType::Solid) {
            return new SolidDrawer;
        }

        if (type == DrawType::Hollow) {
            return new HollowDrawer;
        }

        return nullptr;
    }
};

int main() {
    std::vector<IShape*> shapes = {
        new Rectangle(2, 3),
        new Square(2),
        new Rectangle(4, 6),
        new Square(12),
    };

    std::vector<DrawType> types = {DrawType::Solid, DrawType::Hollow, DrawType::Solid, DrawType::Hollow};
    std::vector<char> chars = {'*', '+', '@', '-'};
    std::vector<Info*> infos;

    for (int i = 0; i < shapes.size(); ++i) {
        infos.push_back(new Info(shapes[i]->type(), types[i], chars[i]));
    }

    DrawFactory factory;

    for (auto& i : infos) {
        IDrawer* drawer = factory.create(i->drawType);
        std::cout << drawer->draw(i);
        delete drawer;
    }

    for (auto& i : infos) {
        delete i;
    }

    for (auto& s : shapes) {
        delete s;
    }
    return 0;
}