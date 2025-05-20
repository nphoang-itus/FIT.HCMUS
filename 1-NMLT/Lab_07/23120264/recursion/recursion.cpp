#include <iostream>
#include <string>

// TODO
#include "recursion.h"

// 8.1 Compute factorial of n
int compute_factorial(int n) {
    if (n <= 1) return 1;
    return n * compute_factorial(n - 1);
}

// 8.2 Compute nth Fibonacci number
int fibonaci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonaci(n - 1) + fibonaci(n - 2);
}

// 8.3 Print numbers from n to 1
void print_reverse(int n) {
    if (n <= 0) return;
    std::cout << n << " ";
    print_reverse(n - 1);
}

// 8.4 Reverse a string
std::string reverse_string(const std::string& s) {
    if (s.length() <= 1) return s;
    return reverse_string(s.substr(1)) + s[0];
}

// 8.5 Find GCD using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 8.6 Count digits in a number
int count_digits(long long n) {
    if (n < 10) return 1;
    return 1 + count_digits(n / 10);
}

// 8.7 Check if array is symmetric
bool is_symetric(const int arr[], int left, int right) {
    if (left >= right) return true;
    if (arr[left] != arr[right]) return false;
    return is_symetric(arr, left + 1, right - 1);
}

// 8.8 Check if string is palindrome
bool is_symetric_string(const std::string& s) {
    if (s.length() <= 1) return true;
    if (s[0] != s[s.length() - 1]) return false;
    return is_symetric_string(s.substr(1, s.length() - 2));
}

// 8.9 Generate all permutations of a string
void permutate(std::string& s, int start, int end) {
    if (start == end) {
        std::cout << s << std::endl;
        return;
    }
    
    for (int i = start; i <= end; i++) {
        std::swap(s[start], s[i]);
    
        permutate(s, start + 1, end);
        
        std::swap(s[start], s[i]);
    }
}

void print_permutation(const std::string& s) {
    std::string str = s;
    permutate(str, 0, str.length() - 1);
}

// 8.10 Count paths in matrix with specific sum
int count_path_helper(int arr[][MAX_COLS], int rows, int cols, int i, int j, int s, int current_sum) {
    // Base cases
    if (i >= rows || j >= cols) return 0;
    
    current_sum += arr[i][j];
    
    if (i == rows - 1 && j == cols - 1) {
        return (current_sum == s) ? 1 : 0;
    }
    
    return count_path_helper(arr, rows, cols, i + 1, j, s, current_sum) + 
           count_path_helper(arr, rows, cols, i, j + 1, s, current_sum);
}

int count_path(int arr[][MAX_COLS], int rows, int cols, int s) {
    return count_path_helper(arr, rows, cols, 0, 0, s, 0);
}
// END TODO