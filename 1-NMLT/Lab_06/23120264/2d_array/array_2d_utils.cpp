#include <iostream>

#include "array_2d_utils.h"
#include "format_utils.h"

using namespace std;

void input_2d(int arr[][MAX_COLS], int rows, int cols) {
    // TODO
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "Enter element [" << i << "][" << j << "]: ";
            std::cin >> arr[i][j];
        }
    }
    // END TODO
}

void print_2d(int arr[][MAX_COLS], int rows, int cols) {
    // TODO
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // END TODO
}

bool check_exist(int arr[][MAX_COLS], int rows, int cols, int value) {
    // TODO
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == value) {
                return true;
            }
        }
    }
    return false;
    // END TODO
}

long long compute_2d(int arr[][MAX_COLS], int rows, int cols, char op) {
    // TODO
    long long result = (op == '*') ? 1 : 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (op == '+') {
                result += arr[i][j];
            } else if (op == '*') {
                result *= arr[i][j];
            }
        }
    }
    
    return result;
    // END TODO
}

float compute_mean_2d(int arr[][MAX_COLS], int rows, int cols) {
    // TODO
    float result = 0.0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result += arr[i][j];
        }
    }
    
    result /= (rows * cols);
    return round_to_decimal(result, 2);
    // END TODO
}

int get_max_min_2d(int arr[][MAX_COLS], int rows, int cols, bool max) {
    // TODO
    int result = arr[0][0];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (max) {
                if (arr[i][j] > result) {
                    result = arr[i][j];
                }
            } else {
                if (arr[i][j] < result) {
                    result = arr[i][j];
                }
            }
        }
    }
    
    return result;
    // END TODO
}

void sort_ascending_2d(int arr[][MAX_COLS], int rows, int cols, bool row_based) {
    // TODO
    if (row_based) {
        // Sort each row
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols - 1; j++) {
                for (int k = 0; k < cols - j - 1; k++) {
                    if (arr[i][k] > arr[i][k + 1]) {
                        int temp = arr[i][k];
                        arr[i][k] = arr[i][k + 1];
                        arr[i][k + 1] = temp;
                    }
                }
            }
        }
    } else {
        // Sort each column
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows - 1; i++) {
                for (int k = 0; k < rows - i - 1; k++) {
                    if (arr[k][j] > arr[k + 1][j]) {
                        int temp = arr[k][j];
                        arr[k][j] = arr[k + 1][j];
                        arr[k + 1][j] = temp;
                    }
                }
            }
        }
    }
    // END TODO
}

void sort_descending_2d(int arr[][MAX_COLS], int rows, int cols, bool row_based) {
    // TODO
    if (row_based) {
        // Sort each row
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols - 1; j++) {
                for (int k = 0; k < cols - j - 1; k++) {
                    if (arr[i][k] < arr[i][k + 1]) {
                        int temp = arr[i][k];
                        arr[i][k] = arr[i][k + 1];
                        arr[i][k + 1] = temp;
                    }
                }
            }
        }
    } else {
        // Sort each column
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows - 1; i++) {
                for (int k = 0; k < rows - i - 1; k++) {
                    if (arr[k][j] < arr[k + 1][j]) {
                        int temp = arr[k][j];
                        arr[k][j] = arr[k + 1][j];
                        arr[k + 1][j] = temp;
                    }
                }
            }
        }
    }
    // END TODO
}

void swap_2d(int arr[][MAX_COLS], int rows, int cols, 
            int first_index, int second_index, bool row_based) {
    // TODO
    if (row_based) {
        // Swap rows
        for (int j = 0; j < cols; j++) {
            int temp = arr[first_index][j];
            arr[first_index][j] = arr[second_index][j];
            arr[second_index][j] = temp;
        }
    } else {
        // Swap columns
        for (int i = 0; i < rows; i++) {
            int temp = arr[i][first_index];
            arr[i][first_index] = arr[i][second_index];
            arr[i][second_index] = temp;
        }
    }
    // END TODO
}

void transpose_2d(int arr[][MAX_COLS], int rows, int cols) {
    // TODO
    // Create a temporary array
    int temp[MAX_ROWS][MAX_COLS];
    
    // Copy the original array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp[i][j] = arr[i][j];
        }
    }
    
    // Transpose
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[j][i] = temp[i][j];
        }
    }
    // END TODO
}

void rotate_2d(int arr[][MAX_COLS], int rows, int cols, int n) {
    // TODO
    // Normalize n to be between 0 and 3
    n = n % 4;
    if (n < 0) n += 4;
    
    for (int rotation = 0; rotation < n; rotation++) {
        // Create a temporary array
        int temp[MAX_ROWS][MAX_COLS];
        
        // Copy the original array
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp[i][j] = arr[i][j];
            }
        }
        
        // Rotate 90 degrees clockwise
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                arr[j][rows - 1 - i] = temp[i][j];
            }
        }
    }
    // END TODO
}

void reverse_2d(int arr[][MAX_COLS], int rows, int cols, bool row_based) {
    // TODO
    if (row_based) {
        // Reverse each row
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols / 2; j++) {
                int temp = arr[i][j];
                arr[i][j] = arr[i][cols - 1 - j];
                arr[i][cols - 1 - j] = temp;
            }
        }
    } else {
        // Reverse each column
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows / 2; i++) {
                int temp = arr[i][j];
                arr[i][j] = arr[rows - 1 - i][j];
                arr[rows - 1 - i][j] = temp;
            }
        }
    }
    // END TODO
}