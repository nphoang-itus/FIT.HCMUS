#include "StackByLinkedList.h"
#include <iostream>

int main() {
    try {
        // Trường hợp bình thường
        StackByLinkedList s;

        for (int i = 0; i < 10; ++i) {
            s.push(i);
        }

        std::cout << s.size() << "\n";

        for (int i = 0; i < 10; ++i) {
            std::cout << s.pop() << " ";
        }

        std::cout << "\nEnter for continue\n";
        std::cin.get();

        // Trường hợp xảy ra lỗi tức pop với 0 phần tử
        std::cout << s.size() << "\n";
        s.pop();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what();
    }
    return 0;
}