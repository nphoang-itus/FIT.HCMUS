#ifndef RECURSION_H
#define RECURSION_H

const int MAX_COLS = 100;
const int MAX_ROWS = 100;

int compute_factorial(int n);

int fibonaci(int n);

void print_reverse(int n);

std::string reverse_string(const std::string& s);

int gcd(int a , int b);

int count_digits(long long n);

bool is_symetric(const int arr[], int left, int right);

bool is_symetric_string(const std::string& s);

void print_permutation(const std::string & s);

int count_path(int arr[][MAX_COLS], int rows, int cols, int s);

#endif