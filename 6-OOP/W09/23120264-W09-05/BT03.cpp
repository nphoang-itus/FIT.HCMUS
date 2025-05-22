#include <iostream>
#include <string>

class PrintConsoleDevice {
private:
    std::ostream* _os;
    PrintConsoleDevice() : _os(&std::cout) {}
public:
    void Print(const std::string& s) { *_os << s; };

    static PrintConsoleDevice GetInstance() {
        static PrintConsoleDevice instance;
        return instance;
    }
};

int main() {
    PrintConsoleDevice print1 = PrintConsoleDevice::GetInstance();
    print1.Print("Su dung in lan 1\n");

    PrintConsoleDevice print2 = PrintConsoleDevice::GetInstance();
    print2.Print("Su dung in lan 2\n");

    return 0;
}