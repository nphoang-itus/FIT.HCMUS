#ifndef SHAPE_TYPE_H
#define SHAPE_TYPE_H

#include <map>
#include <string>

enum class ShapeType {
    RECTANGLE,
    CIRCLE,
    TRIANGLE,
    RIGHT_TRAPEZOID
    // *Có nhu cầu thêm hình sẽ bổ sung ở đây
};

// Hàm thay thế cho inline variable
inline const std::map<ShapeType, std::string>& getPrefix() {
    static const std::map<ShapeType, std::string> mapPrefix {
        {ShapeType::RECTANGLE, "hcn"},
        {ShapeType::CIRCLE, "htr"},
        {ShapeType::TRIANGLE, "htg"},
        {ShapeType::RIGHT_TRAPEZOID, "hthv"}
        // *Có nhu cầu thêm hình sẽ bổ sung ở đây
    };
    return mapPrefix;
}

#endif // SHAPE_TYPE_H