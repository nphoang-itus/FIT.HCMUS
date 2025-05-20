#include <string>
#include <iostream>
#include <vector>
#include <cmath>

class Component {
protected:
    std::string _name;

public:
    virtual ~Component() = default;

    Component(const std::string& s) {
        _name = s;
    }

    virtual int getSize() const = 0;

    void Print(std::ostream& os) const {
        os << _name << " (" << getSize() << ")" << "\n";
    }
};

class Directory : public Component {
private:
    std::vector<Component*> _children;

public:
    Directory(const std::string& s) : Component(s) {}
    
    ~Directory() {
        for (auto x : _children) {
            // std::cout << "delete ";
            // x->Print(std::cout);
            delete x;
        }
    }

    void addChild(Component* c) {
        _children.push_back(c);
    }

    int getSize() const override{
        int total = 0;

        for (const auto& x : _children) {
            total += x->getSize();
        }

        return total;
    }
};

class File : public Component {
private:
    int _size;

public:
    File(const std::string& s, const int& size) : Component(s), _size(std::abs(size)) {}

    int getSize() const override {
        return _size;
    }
};

int main() {
    Directory* dRoot = new Directory("Dir root");
    Directory* dChild = new Directory("Dir child");

    dChild->addChild(new File("File 1", 123));
    dChild->addChild(new File("File 2", 444));

    dRoot->addChild(dChild);
    dRoot->addChild(new File("File 3", 7899));

    dRoot->Print(std::cout);

    std::cout << "\n\n";

    delete dRoot;
    return 0;
}