#ifndef STUDENT_UTILS_H
#define STUDENT_UTILS_H

struct Student {
    std::string name;
    int student_code;
    float score;
};

void read_students(Student students[], int& num_students, std::string file_name = "input_student.txt");

void write_students(Student students[], int& num_students, std::string out_file_name = "output_student.txt");

void search_by_student_code(Student students[], int& num_students, int student_code, std::string out_file_name = "search_sc.txt");

void search_by_name(Student students[], int& num_students, std::string student_name, std::string out_file_name = "search_name.txt");

void remove_student(Student students[], int& num_students, int student_code, std::string out_file_name = "remove_sc.txt");

void sort_by_score(Student students[], int& num_students, std::string out_file_name = "sorted_student.txt");

void average_score(Student students[], int& num_students, std::string out_file_name = "average_score.txt");

void filter_good_students(Student students[], int& num_students, std::string out_file_name = "good_student.txt");

#endif