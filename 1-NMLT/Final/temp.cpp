#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_RESTAURANTS = 100;
const int MAX_DISHES = 4;

struct Restaurant {
    // TODO
    std::string name;
    float scores[MAX_DISHES];
    // END TODO
};

void parseRestaurantLine(const string& line, Restaurant& res) {
    int pos = 0;
    int commaPos = line.find(',');
    res.name = line.substr(0, commaPos);
    pos = commaPos + 1;
    
    for (int i = 0; i < MAX_DISHES; i++) {
        commaPos = line.find(',', pos);
        if (commaPos == string::npos) {
            res.scores[i] = stof(line.substr(pos));
            break;
        } else {
            res.scores[i] = stof(line.substr(pos, commaPos - pos));
            pos = commaPos + 1;
        }
    }
}

bool isUniqueMaxInRow(Restaurant res[MAX_RESTAURANTS], int row, int col, int numDishes) {
    float maxVal = res[row].scores[col];
    int count = 0;
    for (int j = 0; j < numDishes; j++) {
        if (res[row].scores[j] == maxVal) count++;
    }
    return count == 1;
}

bool isUniqueMaxInCol(Restaurant res[MAX_RESTAURANTS], int row, int col, int numRestaurants) {
    float maxVal = res[row].scores[col];
    int count = 0;
    for (int i = 0; i < numRestaurants; i++) {
        if (res[i].scores[col] == maxVal) count++;
    }
    return count == 1;
}

bool isMaxInRow(Restaurant res[MAX_RESTAURANTS], int row, int col, int numDishes) {
    float val = res[row].scores[col];
    for (int j = 0; j < numDishes; j++) {
        if (res[row].scores[j] > val) return false;
    }
    return true;
}

bool isMaxInCol(Restaurant res[MAX_RESTAURANTS], int row, int col, int numRestaurants) {
    float val = res[row].scores[col];
    for (int i = 0; i < numRestaurants; i++) {
        if (res[i].scores[col] > val) return false;
    }
    return true;
}

void find_quality_restaurants(string input_file_name = "restaurants.txt", 
                             string output_file_name = "quality_restaurants.txt") {
    ifstream inFile(input_file_name);
    ofstream outFile(output_file_name);
    
    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return;
    }
    
    int numTestCases;
    inFile >> numTestCases;
    inFile.ignore();
    
    for (int t = 0; t < numTestCases; t++) {
        int numRestaurants;
        inFile >> numRestaurants;
        inFile.ignore();
        
        // float arr2d[MAX_RESTAURANTS][MAX_DISHES];
        // string restaurantNames[MAX_RESTAURANTS];
        Restaurant res[numRestaurants];
        
        for (int i = 0; i < numRestaurants; i++) {
            string line;
            getline(inFile, line);
            // parseRestaurantLine(line, restaurantNames[i], arr2d[i]);
            parseRestaurantLine(line, res[i]);
        }
        
        // Find quality restaurants
        for (int i = 0; i < numRestaurants; i++) {
            for (int j = 0; j < MAX_DISHES; j++) {
                if (
                    isMaxInRow(res, i, j, MAX_DISHES) && 
                    isMaxInCol(res, i, j, numRestaurants) &&
                    isUniqueMaxInRow(res, i, j, MAX_DISHES) &&
                    isUniqueMaxInCol(res, i, j, numRestaurants)
                ) {
                    
                    outFile << res[i].name << ","
                           << res[i].scores[j] << endl;
                }
            }
        }
    }
    
    inFile.close();
    outFile.close();
}
