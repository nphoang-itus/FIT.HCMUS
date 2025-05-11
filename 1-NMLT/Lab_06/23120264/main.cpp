#include <iostream>

#include "1d_array/array_1d_utils.h"
#include "2d_array/array_2d_utils.h"

using namespace std;


int main(){
    // TODO

    // Test array 1D
    const int MAX_SIZE = 100;
    int arr[MAX_SIZE] = {23, 10, 30, 0, 10, 0};
    int n = 6;
    
    std::cout << "=== Testing 1D Array Functions ===\n\n";
    
    // Test input and print
    // std::cout << "1. Testing input_array and print_array:\n";
    // n = 7;
    // std::cout << "Enter 7 elements: ";
    // input_array(arr, n);
    std::cout << "Array after input: ";
    print_array(arr, n);
    std::cout << "\n";
    
    // Test search
    // std::cout << "2. Testing search:\n";
    // int search_value = 20;
    // int search_result = search(arr, n, search_value);
    // std::cout << "Searching for " << search_value << ": Found at index " << search_result << "\n\n";
    
    // // Test remove_at_index
    // std::cout << "3. Testing remove_at_index:\n";
    // int remove_index = 2;  // Remove element at index 2
    // std::cout << "Removing element at index " << remove_index << "\n";
    // std::cout << "Array before removing: ";
    // print_array(arr, n);
    // if (remove_at_index(arr, n, remove_index)) {
    //     std::cout << "Array after removing: ";
    //     print_array(arr, n);
    // } else {
    //     std::cout << "Failed to remove element\n";
    // }
    // std::cout << "\n";
    
    // // Test add_at_index
    // std::cout << "4. Testing add_at_index:\n";
    // int add_value = 5;
    // int add_index = 2;  // Add at the position we just removed
    // std::cout << "Adding " << add_value << " at index " << add_index << "\n";
    // if (add_at_index(arr, n, add_value, add_index)) {
    //     std::cout << "Array after adding: ";
    //     print_array(arr, n);
    // } else {
    //     std::cout << "Failed to add element\n";
    // }
    // std::cout << "\n";
    
    // Test compute_array
    std::cout << "5. Testing compute_array:\n";
    long long sum = compute_array(arr, n, '+');
    long long product = compute_array(arr, n, '*');
    std::cout << "Sum of array: " << sum << "\n";
    std::cout << "Product of array: " << product << "\n\n";
    
    // Test compute_mean
    std::cout << "6. Testing compute_mean:\n";
    float mean = compute_mean(arr, n);
    std::cout << "Mean of array: " << mean << "\n\n";
    
    // Test compute_median
    std::cout << "7. Testing compute_median:\n";
    float median = compute_median(arr, n);
    std::cout << "Median of array: " << median << "\n\n";
    
    // Test get_max_min
    std::cout << "8. Testing get_max_min:\n";
    int max_value = get_max_min(arr, n, true);
    int min_value = get_max_min(arr, n, false);
    std::cout << "Maximum value: " << max_value << "\n";
    std::cout << "Minimum value: " << min_value << "\n\n";
    
    // Test sort_ascending
    std::cout << "9. Testing sort_ascending:\n";
    std::cout << "Array before sorting: ";
    print_array(arr, n);
    sort_ascending(arr, n);
    std::cout << "Array after ascending sort: ";
    print_array(arr, n);
    std::cout << "\n";
    
    // Test sort_descending
    std::cout << "10. Testing sort_descending:\n";
    std::cout << "Array before sorting: ";
    print_array(arr, n);
    sort_descending(arr, n);
    std::cout << "Array after descending sort: ";
    print_array(arr, n);
    std::cout << "\n";

    // Test array 2D
    std::cout << "=== Testing 2D Array Functions ===\n\n";
    
    // Initialize a 3x3 matrix for testing
    int arr2d[MAX_ROWS][MAX_COLS] = {
        {1, 3, 1},
        {4, 6, 5},
        {7, 8, 9}
    };
    int rows = 3, cols = 3;
    
    // Test print_2d
    std::cout << "1. Testing print_2d:\n";
    std::cout << "Original matrix:\n";
    print_2d(arr2d, rows, cols);
    std::cout << "\n";
    
    // Test check_exist
    std::cout << "2. Testing check_exist:\n";
    int search_value = 5;
    bool exists = check_exist(arr2d, rows, cols, search_value);
    std::cout << "Searching for " << search_value << ": " << (exists ? "Found" : "Not found") << "\n\n";
    
    // Test compute_2d
    std::cout << "3. Testing compute_2d:\n";
    long long sum = compute_2d(arr2d, rows, cols, '+');
    long long product = compute_2d(arr2d, rows, cols, '*');
    std::cout << "Sum of matrix: " << sum << "\n";
    std::cout << "Product of matrix: " << product << "\n\n";
    
    // Test compute_mean_2d
    std::cout << "4. Testing compute_mean_2d:\n";
    float mean = compute_mean_2d(arr2d, rows, cols);
    std::cout << "Mean of matrix: " << mean << "\n\n";
    
    // Test get_max_min_2d
    std::cout << "5. Testing get_max_min_2d:\n";
    int max_value = get_max_min_2d(arr2d, rows, cols, true);
    int min_value = get_max_min_2d(arr2d, rows, cols, false);
    std::cout << "Maximum value: " << max_value << "\n";
    std::cout << "Minimum value: " << min_value << "\n\n";
    
    // Test sort_ascending_2d
    std::cout << "6. Testing sort_ascending_2d (row-based):\n";
    std::cout << "Matrix before sorting:\n";
    print_2d(arr2d, rows, cols);
    sort_ascending_2d(arr2d, rows, cols, true);
    std::cout << "Matrix after row-based ascending sort:\n";
    print_2d(arr2d, rows, cols);
    std::cout << "\n";
    
    // Test sort_descending_2d
    std::cout << "7. Testing sort_descending_2d (column-based):\n";
    std::cout << "Matrix before sorting:\n";
    print_2d(arr2d, rows, cols);
    sort_descending_2d(arr2d, rows, cols, false);
    std::cout << "Matrix after column-based descending sort:\n";
    print_2d(arr2d, rows, cols);
    std::cout << "\n";
    
    // Test swap_2d
    std::cout << "8. Testing swap_2d (row swap):\n";
    std::cout << "Matrix before swapping rows 0 and 1:\n";
    print_2d(arr2d, rows, cols);
    swap_2d(arr2d, rows, cols, 0, 1, true);
    std::cout << "Matrix after swapping rows 0 and 1:\n";
    print_2d(arr2d, rows, cols);
    std::cout << "\n";
    
    // Test transpose_2d
    std::cout << "9. Testing transpose_2d:\n";
    std::cout << "Matrix before transpose:\n";
    print_2d(arr2d, rows, cols);
    transpose_2d(arr2d, rows, cols);
    std::cout << "Matrix after transpose:\n";
    print_2d(arr2d, rows, cols);
    std::cout << "\n";
    
    // Test rotate_2d
    std::cout << "10. Testing rotate_2d (rotate 90 degrees):\n";
    std::cout << "Matrix before rotation:\n";
    print_2d(arr2d, rows, cols);
    rotate_2d(arr2d, rows, cols, 1);
    std::cout << "Matrix after 90-degree rotation:\n";
    print_2d(arr2d, rows, cols);
    std::cout << "\n";
    
    // Test reverse_2d
    std::cout << "11. Testing reverse_2d (row-based):\n";
    std::cout << "Matrix before row reversal:\n";
    print_2d(arr2d, rows, cols);
    reverse_2d(arr2d, rows, cols, false);
    std::cout << "Matrix after row reversal:\n";
    print_2d(arr2d, rows, cols);
    std::cout << "\n";

    // END TODO
    return 0;
}