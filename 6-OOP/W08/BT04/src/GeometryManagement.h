#ifndef GEOMETRY_MANAGEMENT_H
#define GEOMETRY_MANAGEMENT_H

#include "Geometry.h"
#include "GeometryRegistry.h"
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <numeric>

class GeometryManagement {
private:
    std::vector<std::unique_ptr<Geometry>> _geometryList;

public:
    void addGeometry(std::unique_ptr<Geometry> geo);
    void readListFromFile(const std::string& fileName);
    
    int countShapesByType(ShapeType type) const;
    double sumOfPerimeter() const;
    double sumOfArea() const;
    
    friend std::ostream& operator<<(std::ostream& os, const GeometryManagement& geoMana);
    
    size_t size() const { return _geometryList.size(); }
    void listRegisteredShapes() const {
        GeometryRegistry::getInstance().listRegisteredShapes();
    }
    int numberOfShapeTypes() const {
        return GeometryRegistry::getInstance().numberOfShapeTypes();
    }
};

#endif // GEOMETRY_MANAGEMENT_H