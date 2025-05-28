#include <iostream>

#include "restaurant_helper/restaurant_utils.h"

using namespace std;

int find_unique_students(int ids[], int n) {
    int result = 0;
    // TODO
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (ids[i] == ids[j]) {
                count++;
            }
        }
        if (count == 1) {
            result++;
        }
    }
    // END TODO
    return result;
}

int main() {
    // int ids[] = {101, 102, 103, 101, 104, 102};
    int ids[] = {2001, 2002, 2003, 2004, 2005, 2006};
    int n = sizeof(ids) / sizeof(ids[0]);
    cout << find_unique_students(ids, n) << endl;
    
    find_quality_restaurants("restaurant_helper/data/restaurants.txt",
                        "restaurant_helper/result/quality_restaurants.txt");
    return 0;
}