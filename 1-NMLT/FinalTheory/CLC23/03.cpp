#include <iostream>

int convert(char str[]) {
    int res = str[0] - 'a';
    for (int i = 1; i < std::strlen(str); ++i)
        res = res * 10 + (str[i] - 'a');
    return res;
}

bool checkEqual(char first[], char second[], char target[]) {
    return convert(first) + convert(second) == convert(target);
}

int main() {
    // test case 1
    char first[] = "bac";
    char second[] = "ba";
    char target[] = "bbc";
    std::cout << checkEqual(first, second, target) << "\n";

    // test case 1
    char f2[] = "ad";
    char s2[] = "da";
    char t2[] = "dad";
    std::cout << checkEqual(f2, s2, t2) << "\n";

    return 0;
}