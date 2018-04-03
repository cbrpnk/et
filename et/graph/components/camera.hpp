#pragma once

#include <iostream>
#include "component.hpp"
#include "math/functions.hpp"

namespace Et {
namespace Graph {

class Obj;

class Camera : public Component {
public:
    enum class AspectRatio {
        R11,
        R21,
        R43,
        R169
    };

public:
    Camera(Obj& obj, AspectRatio apectRatio, float fov, float dof);
    
    virtual void update() override {}
    
    float getSensorWidth()  const { return sensorWidth_; }
    float getSensorHeight() const { return sensorHeight_; }
    float getFieldOfView()  const { return fieldOfView_; }
    float getFocalLength()  const { return focalLength_; }
    float getDepthOfField() const { return depthOfField_; }
    
    void setAspectRatio(AspectRatio r);

private:
    float       sensorWidth_;
    float       sensorHeight_;
    AspectRatio aspectRatio_;
    // Horizontal field of view
    float       fieldOfView_;
    // Distance of the sensor, deduced from the field of view
    float       focalLength_;
    // Distance to the focal plane
    float       depthOfField_;
};

} // namespace Graph
} // namespace Et
