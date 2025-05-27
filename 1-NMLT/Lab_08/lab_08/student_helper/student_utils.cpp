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


// END TODO