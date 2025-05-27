#include <iostream>

#include "fraction_helper/fraction_utils.h"
#include "student_helper/student_utils.h"

using namespace std;

// TODO
void test_fraction_operations() {
    cout << "=== Testing Fraction Operations ===" << endl;
    // Test basic operations
    Fraction f1 = {1, 2};  // 1/2
    Fraction f2 = {3, 4};  // 3/4
    
    cout << "Testing with fractions 1/2 and 3/4:" << endl;
    
    Fraction sum = sum_fraction(f1, f2);
    cout << "Sum: " << sum.numerator << "/" << sum.denominator << endl;
    
    Fraction diff = minus_fraction(f1, f2);
    cout << "Difference: " << diff.numerator << "/" << diff.denominator << endl;
    
    Fraction product = multiply_fraction(f1, f2);
    cout << "Product: " << product.numerator << "/" << product.denominator << endl;
    
    Fraction quotient = divide_fraction(f1, f2);
    cout << "Quotient: " << quotient.numerator << "/" << quotient.denominator << endl;
    
    cout << "Is 1/2 equal to 3/4? " << (is_equal(f1, f2) ? "Yes" : "No") << endl;
    cout << "Is 1/2 greater than 3/4? " << (is_greater(f1, f2) ? "Yes" : "No") << endl;
    cout << "Is 1/2 less than 3/4? " << (is_less(f1, f2) ? "Yes" : "No") << endl;
    
    cout << "\nTesting auto_test_fraction..." << endl;
    std::string inputFile = "fraction_helper/test_result/input_fraction.txt";
    std::string outputFile = "fraction_helper/test_result/output_fraction.txt";

    auto_test_fraction(inputFile, outputFile);
    cout << "Check output_fraction.txt for results." << endl;
}

void test_student_operations() {
    cout << "\n=== Testing Student Operations ===" << endl;
    
    const int MAX_STUDENTS = 1000;
    Student students[MAX_STUDENTS];
    int num_students = 0;

    std::string root_direct_input = "student_helper/data/";
    std::string root_direct_output = "student_helper/result/";
    
    // Read students from file
    read_students(students, num_students, root_direct_input + "input_student.txt");
    cout << "Read " << num_students << " students from file." << endl;
    
    // Write students to output file
    write_students(students, num_students, root_direct_output + "output_student.txt");
    cout << "Written students to output_student.txt" << endl;
    
    // Search by student code
    search_by_student_code(students, num_students, 123458, root_direct_output + "search_sc.txt");
    cout << "Searched for student code 123458, result in search_sc.txt" << endl;
    
    // Search by name
    search_by_name(students, num_students, "Van C", root_direct_output + "search_name.txt");
    cout << "Searched for name containing 'Van C', result in search_name.txt" << endl;
    
    // Remove student
    remove_student(students, num_students, 123459, root_direct_output + "remove_sc.txt");
    cout << "Removed student 123459, remaining students in remove_sc.txt" << endl;
    
    // Sort by score
    sort_by_score(students, num_students, root_direct_output + "sorted_student.txt");
    cout << "Sorted students by score, result in sorted_student.txt" << endl;
    
    // Calculate average score
    average_score(students, num_students, root_direct_output + "avarage_score.txt");
    cout << "Calculated average score, result in average_score.txt" << endl;
    
    // Filter good students
    filter_good_students(students, num_students, root_direct_output + "good_student.txt");
    cout << "Filtered good students (score >= 8.0), result in good_student.txt" << endl;
}
// END TODO


int main () {
    // TODO
    // test_fraction_operations();
    test_student_operations();
    // END TODO
    return 0;
}