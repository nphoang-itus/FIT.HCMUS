#ifndef RIGHT_TRAPEZOID_H
#define RIGHT_TRAPEZOID_H

#include "Geometry.h"

class RightTrapezoid : public Geometry {
private:
    float _topSide;
    float _bottomSide;
    float _height;
    
public:
    RightTrapezoid();
    RightTrapezoid(const float& topSide, const float& bottomSide, const float& height);

    ShapeType getShapeType() const override;
    
    float getTopSide() const;
    float getBottomSide() const;
    float getHeight() const;
    
    void setTopSide(const float& topSide);
    void setBottomSide(const float& bottomSide);
    void setHeight(const float& height);
    
    // Cạnh bên nghiêng (tính bằng định lý Pythagoras)
    float calculateSlantSide() const;
    
    double calculatePerimeter() const override;
    double calculateArea() const override;
    
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    
    friend std::ostream& operator<<(std::ostream& os, const RightTrapezoid& trap);
    friend std::istream& operator>>(std::istream& is, RightTrapezoid& trap);
};

#endif // RIGHT_TRAPEZOID_H