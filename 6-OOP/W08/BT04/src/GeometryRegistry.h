#ifndef GEOMETRY_REGISTRY_H
#define GEOMETRY_REGISTRY_H

#include "GeometryFactory.h"
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

// Registry Pattern để quản lý các factory
class GeometryRegistry {
private:
    std::map<std::string, std::unique_ptr<GeometryFactory>> _factories;
    
    // Singleton pattern
    GeometryRegistry() {
        // Đăng ký các factory mặc định
        registerFactory(std::make_unique<RectangleFactory>());
        registerFactory(std::make_unique<CircleFactory>());
        registerFactory(std::make_unique<TriangleFactory>());
        registerFactory(std::make_unique<RightTrapezoidFactory>());
    }
    
    GeometryRegistry(const GeometryRegistry&) = delete;
    GeometryRegistry& operator=(const GeometryRegistry&) = delete;
    
public:
    static GeometryRegistry& getInstance() {
        static GeometryRegistry instance;
        return instance;
    }
    
    void registerFactory(std::unique_ptr<GeometryFactory> factory) {
        std::string prefix = factory->getShapePrefix();
        _factories[prefix] = std::move(factory);
    }
    
    std::unique_ptr<Geometry> createGeometry(const std::string& line) {
        std::istringstream iss(line);
        std::string prefix;
        std::getline(iss, prefix, ':');
        
        std::string data;
        std::getline(iss, data);
        
        auto it = _factories.find(prefix);
        if (it != _factories.end()) {
            return it->second->createGeometry(data);
        }
        
        std::cerr << "Không hỗ trợ loại hình: " << prefix << std::endl;
        return nullptr;
    }
    
    // Phương thức để liệt kê các loại hình đã đăng ký
    void listRegisteredShapes() const {
        std::cout << "Các loại hình đã đăng ký:\n";
        for (const auto& pair : _factories) {
            std::cout << "- " << pair.first << "\n";
        }
    }

    int numberOfShapeTypes() const {
        return _factories.size();
    }
};

#endif // GEOMETRY_REGISTRY_H