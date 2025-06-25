#include <iostream>

int main() {
    int x = 5;
    
    if (x > 0) {
        goto positive;
    }
    
    std::cout << "Number is not positive" << std::endl;
    goto end;
    
positive:
    std::cout << "Number is positive" << std::endl;
    
end:
    std::cout << "Program ends" << std::endl;
    return 0;
}