#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "fraction_utils.h"

using namespace std;

// TODO
// Helper function to find GCD
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Helper function to find LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

Fraction reduce_fraction(const Fraction& fraction) {
    Fraction result = fraction;
    int common_divisor = gcd(abs(result.numerator), abs(result.denominator));
    result.numerator /= common_divisor;
    result.denominator /= common_divisor;
    
    // Handle negative signs
    if (result.denominator < 0) {
        result.numerator = -result.numerator;
        result.denominator = -result.denominator;
    }
    
    return result;
}

Fraction sum_fraction(const Fraction& first_fraction, const Fraction& second_fraction) {
    Fraction result;
    result.denominator = lcm(first_fraction.denominator, second_fraction.denominator);
    result.numerator = (first_fraction.numerator * (result.denominator / first_fraction.denominator)) +
                      (second_fraction.numerator * (result.denominator / second_fraction.denominator));
    return reduce_fraction(result);
}

Fraction minus_fraction(const Fraction& first_fraction, const Fraction& second_fraction) {
    Fraction result;
    result.denominator = lcm(first_fraction.denominator, second_fraction.denominator);
    result.numerator = (first_fraction.numerator * (result.denominator / first_fraction.denominator)) -
                      (second_fraction.numerator * (result.denominator / second_fraction.denominator));
    return reduce_fraction(result);
}

Fraction multiply_fraction(const Fraction& first_fraction, const Fraction& second_fraction) {
    Fraction result;
    result.numerator = first_fraction.numerator * second_fraction.numerator;
    result.denominator = first_fraction.denominator * second_fraction.denominator;
    return reduce_fraction(result);
}

Fraction divide_fraction(const Fraction& first_fraction, const Fraction& second_fraction) {
    Fraction result;
    result.numerator = first_fraction.numerator * second_fraction.denominator;
    result.denominator = first_fraction.denominator * second_fraction.numerator;
    return reduce_fraction(result);
}

bool is_equal(const Fraction& first_fraction, const Fraction& second_fraction) {
    Fraction f1 = reduce_fraction(first_fraction);
    Fraction f2 = reduce_fraction(second_fraction);
    return (f1.numerator == f2.numerator) && (f1.denominator == f2.denominator);
}

bool is_greater(const Fraction& first_fraction, const Fraction& second_fraction) {
    int common_denom = lcm(first_fraction.denominator, second_fraction.denominator);
    int num1 = first_fraction.numerator * (common_denom / first_fraction.denominator);
    int num2 = second_fraction.numerator * (common_denom / second_fraction.denominator);
    return num1 > num2;
}

bool is_less(const Fraction& first_fraction, const Fraction& second_fraction) {
    int common_denom = lcm(first_fraction.denominator, second_fraction.denominator);
    int num1 = first_fraction.numerator * (common_denom / first_fraction.denominator);
    int num2 = second_fraction.numerator * (common_denom / second_fraction.denominator);
    return num1 < num2;
}

// Helper function to parse fraction from string
Fraction parse_fraction(const string& str) {
    Fraction frac;
    size_t slash_pos = str.find('/');
    frac.numerator = stoi(str.substr(0, slash_pos));
    frac.denominator = stoi(str.substr(slash_pos + 1));
    return frac;
}

// Helper function to format fraction output
string format_fraction(const Fraction& frac) {
    Fraction reduced = reduce_fraction(frac);
    if (reduced.denominator == 1) {
        return to_string(reduced.numerator);
    }
    return to_string(reduced.numerator) + "/" + to_string(reduced.denominator);
}

void auto_test_fraction(string input_file_name, string output_file_name) {
    ifstream input_file(input_file_name);
    ofstream output_file(output_file_name);
    
    if (!input_file.is_open() || !output_file.is_open()) {
        return;
    }
    
    int num_tests;
    input_file >> num_tests;
    input_file.ignore(); // ignore newline after number
    
    for (int i = 0; i < num_tests; i++) {
        string operation;
        string fraction_line;
        
        getline(input_file, operation);
        getline(input_file, fraction_line);
        
        // Parse fractions from line using dynamic array
        Fraction* fractions = new Fraction[100];
        int fraction_count = 0;
        
        stringstream ss(fraction_line);
        string fraction_str;
        
        while (getline(ss, fraction_str, ',')) {
            // Remove leading/trailing spaces
            size_t start = fraction_str.find_first_not_of(" \t");
            size_t end = fraction_str.find_last_not_of(" \t");
            if (start != string::npos && end != string::npos) {
                fraction_str = fraction_str.substr(start, end - start + 1);
            }
            fractions[fraction_count] = parse_fraction(fraction_str);
            fraction_count++;
        }
        
        // Perform operation
        if (operation == "+") {
            Fraction result = fractions[0];
            for (int j = 1; j < fraction_count; j++) {
                result = sum_fraction(result, fractions[j]);
            }
            output_file << format_fraction(result) << endl;
        }
        else if (operation == "-") {
            Fraction result = fractions[0];
            for (int j = 1; j < fraction_count; j++) {
                result = minus_fraction(result, fractions[j]);
            }
            output_file << format_fraction(result) << endl;
        }
        else if (operation == "*") {
            Fraction result = fractions[0];
            for (int j = 1; j < fraction_count; j++) {
                result = multiply_fraction(result, fractions[j]);
            }
            output_file << format_fraction(result) << endl;
        }
        else if (operation == "/") {
            Fraction result = fractions[0];
            for (int j = 1; j < fraction_count; j++) {
                result = divide_fraction(result, fractions[j]);
            }
            output_file << format_fraction(result) << endl;
        }
        else if (operation == "=") {
            output_file << (is_equal(fractions[0], fractions[1]) ? "1" : "0") << endl;
        }
        else if (operation == ">") {
            output_file << (is_greater(fractions[0], fractions[1]) ? "1" : "0") << endl;
        }
        else if (operation == "<") {
            output_file << (is_less(fractions[0], fractions[1]) ? "1" : "0") << endl;
        }
        
        delete[] fractions;
    }
    
    input_file.close();
    output_file.close();
}
// END TODO