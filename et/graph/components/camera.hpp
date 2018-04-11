#pragma once

#include <iostream>
#include "component.hpp"
#include "math/functions.hpp"

namespace Et {
namespace Graph {

class Obj;

class Camera : public Component {
public:
    
    struct AspectRatio {
        AspectRatio(float width, float height) : width(width), height(height) {}
        float width;
        float height;
    };

public:
    Camera(Obj& obj, AspectRatio apectRatio, float fov, float focalLength, float fStop);
    
    virtual void update() override {}
    
    float getFocalPlaneWidth()  const { return focalPlane_.width; }
    float getFocalPlaneHeight() const { return focalPlane_.height; }
    float getFieldOfView()      const { return fieldOfView_; }
    float getFocalLength()      const { return focalLength_; }
    float getAperture()         const { return aperture_; }
    
private:
    AspectRatio aspectRatio_;
    // Horizontal field of view
    float       fieldOfView_;
    // Distance of the camera position to the focal plane
    float       focalLength_;
    // Ratio of focalLength over the aperture size
    float       fStop_;
    // Diameter of the aperture
    float       aperture_;
    
    struct FocalPlane {
        FocalPlane() : width(1), height(1) {}
        FocalPlane(float width, float height) : width(width), height(height) {}
        float width;
        float height;
    } focalPlane_;
};

} // namespace Graph
} // namespace Et
