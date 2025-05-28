#ifndef RESTAURANT_UTILS_H
#define RESTAURANT_UTILS_H

const int MAX_RESTAURANTS = 100;
const int MAX_DISHES = 4;

struct Restaurant {
    // TODO
    std::string name;
    float scores[MAX_DISHES];
    // END TODO
};

void find_quality_restaurants(std::string input_file_name = "restaurants.txt",
                        std::string output_file_name = "quality_restaurants.txt");
#endif