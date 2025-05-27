#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "student_utils.h"

using namespace std;

float round_to_decimal(float var, int decimal_places) {
    float factor = pow(10.0f, decimal_places);
    return round(var * factor) / factor;
}

// TODO
void read_students(Student students[], int& num_students, string file_name) {
    ifstream input_file(file_name);
    if (!input_file.is_open()) {
        num_students = 0;
        return;
    }
    
    num_students = 0;
    string line;
    
    while (getline(input_file, line) && num_students < 1000) {
        stringstream ss(line);
        string name, student_code_str, score_str;
        
        // Parse name (everything before the last two commas)
        size_t last_comma = line.find_last_of(',');
        size_t second_last_comma = line.find_last_of(',', last_comma - 1);
        
        name = line.substr(0, second_last_comma);
        student_code_str = line.substr(second_last_comma + 1, last_comma - second_last_comma - 1);
        score_str = line.substr(last_comma + 1);
        
        // Remove leading/trailing spaces
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        student_code_str.erase(0, student_code_str.find_first_not_of(" \t"));
        student_code_str.erase(student_code_str.find_last_not_of(" \t") + 1);
        score_str.erase(0, score_str.find_first_not_of(" \t"));
        score_str.erase(score_str.find_last_not_of(" \t") + 1);
        
        students[num_students].name = name;
        students[num_students].student_code = stoi(student_code_str);
        students[num_students].score = stof(score_str);
        num_students++;
    }
    
    input_file.close();
}

void write_students(Student students[], int& num_students, string out_file_name) {
    ofstream output_file(out_file_name);
    if (!output_file.is_open()) {
        return;
    }
    
    for (int i = 0; i < num_students; i++) {
        output_file << students[i].name << ", " << students[i].student_code << ", " << students[i].score << endl;
    }
    
    output_file.close();
}

void search_by_student_code(Student students[], int& num_students, int student_code, string out_file_name) {
    ofstream output_file(out_file_name);
    if (!output_file.is_open()) {
        return;
    }
    
    for (int i = 0; i < num_students; i++) {
        if (students[i].student_code == student_code) {
            output_file << students[i].name << ", " << students[i].student_code << ", " << students[i].score << endl;
            break;
        }
    }
    
    output_file.close();
}

void search_by_name(Student students[], int& num_students, string student_name, string out_file_name) {
    ofstream output_file(out_file_name);
    if (!output_file.is_open()) {
        return;
    }
    
    for (int i = 0; i < num_students; i++) {
        if (students[i].name.find(student_name) != string::npos) {
            output_file << students[i].name << ", " << students[i].student_code << ", " << students[i].score << endl;
        }
    }
    
    output_file.close();
}

void remove_student(Student students[], int& num_students, int student_code, string out_file_name) {
    // Find and remove student
    for (int i = 0; i < num_students; i++) {
        if (students[i].student_code == student_code) {
            // Shift all elements after index i to the left
            for (int j = i; j < num_students - 1; j++) {
                students[j] = students[j + 1];
            }
            num_students--;
            break;
        }
    }
    
    // Write remaining students to file
    ofstream output_file(out_file_name);
    if (!output_file.is_open()) {
        return;
    }
    
    for (int i = 0; i < num_students; i++) {
        output_file << students[i].name << ", " << students[i].student_code << ", " << students[i].score << endl;
    }
    
    output_file.close();
}

void sort_by_score(Student students[], int& num_students, string out_file_name) {
    // Bubble sort by score (ascending)
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = 0; j < num_students - i - 1; j++) {
            if (students[j].score > students[j + 1].score) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    // Write sorted students to file
    ofstream output_file(out_file_name);
    if (!output_file.is_open()) {
        return;
    }
    
    for (int i = 0; i < num_students; i++) {
        output_file << students[i].name << ", " << students[i].student_code << ", " << students[i].score << endl;
    }
    
    output_file.close();
}

void average_score(Student students[], int& num_students, string out_file_name) {
    if (num_students == 0) {
        return;
    }
    
    float total_score = 0.0;
    for (int i = 0; i < num_students; i++) {
        total_score += students[i].score;
    }
    
    float average = total_score / num_students;
    average = round_to_decimal(average, 2);
    
    ofstream output_file(out_file_name);
    if (!output_file.is_open()) {
        return;
    }
    
    output_file << average << endl;
    output_file.close();
}

void filter_good_students(Student students[], int& num_students, string out_file_name) {
    ofstream output_file(out_file_name);
    if (!output_file.is_open()) {
        return;
    }
    
    for (int i = 0; i < num_students; i++) {
        if (students[i].score >= 8.0) {
            output_file << students[i].name << ", " << students[i].student_code << ", " << students[i].score << endl;
        }
    }
    
    output_file.close();
}
// END TODO