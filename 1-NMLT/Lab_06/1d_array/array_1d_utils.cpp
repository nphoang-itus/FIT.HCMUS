#include <iostream>

#include "array_1d_utils.h"
#include "format_utils.h"

void input_array(int arr[], int n) {
    // TODO
    for (int i = 0; i < n; i++) {
        std::cout << "Enter element " << i + 1 << ": ";
        std::cin >> arr[i];
    }
    // END TODO
}

void print_array(int arr[], int n) {
    // TODO
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    // END TODO
}

int search(int arr[], int n, int value) {
    // TODO
    for (int i = 0; i < n; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
    // END TODO
}

bool add_at_index(int arr[], int& n, int value, int index) {
    // TODO
    if (index < 0 || index > n) {
        return false;
    }
    
    for (int i = n; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    n++;
    return true;
    // END TODO
}

bool remove_at_index(int arr[], int& n, int index) {
    // TODO
    if (index < 0 || index >= n) {
        return false;
    }
    
    for (int i = index; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;
    return true;
    // END TODO
}

long long compute_array(int arr[], int n, char op) {
    // TODO
    long long result = (op == '*') ? 1 : 0;
    
    for (int i = 0; i < n; i++) {
        if (op == '+') {
            result += arr[i];
        } else if (op == '*') {
            result *= arr[i];
        }
    }
    
    return result;
    // END TODO
}

float compute_mean(int arr[], int n) {
    // TODO
    float result = 0.0;
    
    for (int i = 0; i < n; i++) {
        result += arr[i];
    }
    
    result /= n;
    return round_to_decimal(result, 2);
    // END TODO
}

float compute_median(int arr[], int n) {
    // TODO
    float result = 0.0;
    
    // Create a temporary array for sorting
    int temp[n];
    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }
    
    // Sort the temporary array
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }
    
    if (n % 2 == 0) {
        result = (temp[n/2 - 1] + temp[n/2]) / 2.0;
    } else {
        result = temp[n/2];
    }
    
    return round_to_decimal(result, 2);
    // END TODO
}

int get_max_min(int arr[], int n, bool max) {
    // TODO
    int result = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (max) {
            if (arr[i] > result) {
                result = arr[i];
            }
        } else {
            if (arr[i] < result) {
                result = arr[i];
            }
        }
    }
    
    return result;
    // END TODO
}

void sort_ascending(int arr[], int n) {
    // TODO
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
    // END TODO
}

void sort_descending(int arr[], int n) {
    // TODO
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
    // END TODO
}

