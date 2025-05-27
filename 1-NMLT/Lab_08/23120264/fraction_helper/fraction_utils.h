#ifndef FRACTION_UTILS_H
#define FRACTION_UTILS_H

struct Fraction {
    int numerator;
    int denominator;
};

Fraction reduce_fraction(const Fraction& fraction);

Fraction sum_fraction(const Fraction& first_fraction, const Fraction& second_fraction);

Fraction minus_fraction(const Fraction& first_fraction, const Fraction& second_fraction);

Fraction multiply_fraction(const Fraction& first_fraction, const Fraction& second_fraction);

Fraction divide_fraction(const Fraction& first_fraction, const Fraction& second_fraction);

bool is_equal(const Fraction& first_fraction, const Fraction& second_fraction);
        
bool is_greater(const Fraction& first_fraction, const Fraction& second_fraction);
        
bool is_less(const Fraction& first_fraction, const Fraction& second_fraction);

void auto_test_fraction(std::string input_file_name = "input_fraction.txt",
                        std::string output_file_name = "output_fraction.txt");

#endif