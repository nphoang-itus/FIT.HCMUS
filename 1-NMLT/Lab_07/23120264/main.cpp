#include <iostream>
#include "recursion/recursion.h"

using namespace std;

int main(){
    // TODO
    cout << "\n===== RECURSION FUNCTION TESTING =====\n\n";
    
    // 1. Test factorial
    cout << "1. FACTORIAL TEST\n";
    int factorialTests[] = {0, 1, 5, 10};
    for (int n : factorialTests) {
        cout << n << "! = " << compute_factorial(n) << endl;
    }
    cout << "\n";
    
    // 2. Test Fibonacci
    cout << "2. FIBONACCI TEST\n";
    int fibTests[] = {0, 1, 2, 5, 10};
    for (int n : fibTests) {
        cout << "F(" << n << ") = " << fibonaci(n) << endl;
    }
    cout << "\n";
    
    // 3. Test print_reverse
    cout << "3. PRINT_REVERSE TEST\n";
    int printTests[] = {5, 10};
    for (int n : printTests) {
        cout << "Numbers from " << n << " to 1: ";
        print_reverse(n);
        cout << endl;
    }
    cout << "\n";
    
    // 4. Test reverse_string
    cout << "4. REVERSE_STRING TEST\n";
    string strTests[] = {"hello", "recursion", "a", "", "12345"};
    for (const string& s : strTests) {
        cout << "Original: \"" << s << "\" -> Reversed: \"" << reverse_string(s) << "\"" << endl;
    }
    cout << "\n";
    
    // 5. Test GCD
    cout << "5. GCD TEST\n";
    pair<int, int> gcdTests[] = {{12, 18}, {35, 49}, {48, 18}, {17, 13}, {100, 10}};
    for (const auto& p : gcdTests) {
        cout << "GCD(" << p.first << ", " << p.second << ") = " << gcd(p.first, p.second) << endl;
    }
    cout << "\n";
    
    // 6. Test count_digits
    cout << "6. COUNT_DIGITS TEST\n";
    long long digitTests[] = {0, 5, 123, 9876, 1000000};
    for (long long n : digitTests) {
        cout << "Number of digits in " << n << ": " << count_digits(n) << endl;
    }
    cout << "\n";
    
    // 7. Test is_symetric for array
    cout << "7. IS_SYMMETRIC ARRAY TEST\n";
    int arr1[] = {1, 2, 3, 2, 1};
    int arr2[] = {1, 2, 3, 3, 2, 1};
    int arr3[] = {1, 2, 3, 4};
    int arr4[] = {5};
    
    cout << "Array {1, 2, 3, 2, 1}: " << (is_symetric(arr1, 0, 4) ? "Symmetric" : "Not symmetric") << endl;
    cout << "Array {1, 2, 3, 3, 2, 1}: " << (is_symetric(arr2, 0, 5) ? "Symmetric" : "Not symmetric") << endl;
    cout << "Array {1, 2, 3, 4}: " << (is_symetric(arr3, 0, 3) ? "Symmetric" : "Not symmetric") << endl;
    cout << "Array {5}: " << (is_symetric(arr4, 0, 0) ? "Symmetric" : "Not symmetric") << endl;
    cout << "\n";
    
    // 8. Test is_symetric_string
    cout << "8. IS_SYMMETRIC STRING TEST\n";
    string palindromeTests[] = {"racecar", "level", "hello", "a", "", "noon"};
    for (const string& s : palindromeTests) {
        cout << "\"" << s << "\": " << (is_symetric_string(s) ? "Palindrome" : "Not palindrome") << endl;
    }
    cout << "\n";
    
    // 9. Test print_permutation
    cout << "9. PRINT_PERMUTATION TEST\n";
    string permTests[] = {"ABC", "12"};
    for (const string& s : permTests) {
        cout << "Permutations of \"" << s << "\":" << endl;
        print_permutation(s);
        cout << endl;
    }
    
    // 10. Test count_path
    cout << "10. COUNT_PATH TEST\n";
    
    // Test case 1: 2x2 matrix, target sum = 7
    int matrix1[MAX_ROWS][MAX_COLS] = {
        {1, 2},
        {3, 1}
    };
    cout << "Matrix 2x2 [1,2; 3,1], Target sum = 7: " 
         << count_path(matrix1, 2, 2, 7) << " paths" << endl;
    
    // Test case 2: 3x3 matrix, target sum = 11
    int matrix2[MAX_ROWS][MAX_COLS] = {
        {1, 2, 3},
        {4, 1, 2},
        {2, 3, 1}
    };
    cout << "Matrix 3x3 [1,2,3; 4,1,2; 2,3,1], Target sum = 11: " 
         << count_path(matrix2, 3, 3, 11) << " paths" << endl;
    
    // Test case 3: 3x3 matrix, target sum = 15
    cout << "Matrix 3x3 [1,2,3; 4,1,2; 2,3,1], Target sum = 15: " 
         << count_path(matrix2, 3, 3, 15) << " paths" << endl;
         
    cout << "\n===== ALL TESTS COMPLETED =====\n\n";
    // END TODO
    return 0;
}