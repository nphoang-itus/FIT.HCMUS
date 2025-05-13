#ifndef GEOMETRY_FACTORY_H
#define GEOMETRY_FACTORY_H

#include "Geometry.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "RightTrapezoid.h"
#include "ShapeType.h"
#include <memory>
#include <string>

// Interface cho Factory
class GeometryFactory {
public:
    virtual ~GeometryFactory() = default;
    virtual std::unique_ptr<Geometry> createGeometry(const std::string& data) = 0; // Tạo đối tượng hình
    virtual std::string getShapePrefix() const = 0; // Lấy tên hình
};

// Concrete Factory cho Rectangle
class RectangleFactory : public GeometryFactory {
public:
    std::unique_ptr<Geometry> createGeometry(const std::string& data) override;
    std::string getShapePrefix() const override { return getPrefix().at(ShapeType::RECTANGLE); }
};

// Concrete Factory cho Circle
class CircleFactory : public GeometryFactory {
public:
    std::unique_ptr<Geometry> createGeometry(const std::string& data) override;
    std::string getShapePrefix() const override { return getPrefix().at(ShapeType::CIRCLE); }
};

// Concrete Factory cho Triangle
class TriangleFactory : public GeometryFactory {
public:
    std::unique_ptr<Geometry> createGeometry(const std::string& data) override;
    std::string getShapePrefix() const override { return getPrefix().at(ShapeType::TRIANGLE); }
};

// Concrete Factory cho RightTrapezoid
class RightTrapezoidFactory : public GeometryFactory {
public:
    std::unique_ptr<Geometry> createGeometry(const std::string& data) override;
    std::string getShapePrefix() const override { return getPrefix().at(ShapeType::RIGHT_TRAPEZOID); }
};

#endif // GEOMETRY_FACTORY_H