#ifndef ARRAY_1D_UTILS_H
#define ARRAY_1D_UTILS_H

void input_array(int arr[], int n);

void print_array(int arr[], int n);

int search(int arr[], int n, int value);

bool add_at_index(int arr[], int& n, int value, int index);

bool remove_at_index(int arr[], int& n, int index);

long long compute_array(int arr[], int n, char op = '+');

float compute_mean(int arr[], int n);

float compute_median(int arr[], int n);

int get_max_min(int arr[], int n, bool max = true);

void sort_ascending(int arr[], int n);

void sort_descending(int arr[], int n);

#endif