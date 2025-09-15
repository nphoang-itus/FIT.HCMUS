#include <iostream>

// class Cat {
// private:
//     int weight;
//     int height;
// public:
//     void run() {
//         std::cout << "The cat (" << weight << ")" << " Clap clap\n";
//     }
    
//     void sleep();
//     void eat();
// };

struct Cat {
private:
    int weight;
    int height;
public:
    void run() {
        std::cout << "The cat (" << weight << ")" << " Clap clap\n";
    }
    
    void sleep();
    void eat();
};

class Cat {
    int attribute;
};

struct Cat {
    int attribute;
};

class Square {
private:
    int radius;
public:
    const float PI = 3.1415;
    float area();
    float perimeter();
};

class Triangle {
private:
    int edgeA;
    int edgeB;
    int edgeC;

    bool isValidTriangle() {
        return true;
    }
public:
    float area() {
    }
    
    float perimeter() {
        if (isValidTriangle()) {
            return edgeA + edgeB + edgeC;
        }
        return 0.0;
    }
};


int main() {
    // Cat kitty;
    // std::cout << kitty.height << "\n";
    
    // kitty.run();

    return 0;
}