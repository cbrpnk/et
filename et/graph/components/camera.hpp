#pragma once

#include <iostream>
#include "component.hpp"
#include "../../math/functions.hpp"

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
    
    float getSensorWidth()  const { return sensorWidth; }
    float getSensorHeight() const { return sensorHeight; }
    float getFieldOfView()  const { return fieldOfView; }
    float getFocalLength()  const { return focalLength; }
    float getDepthOfField() const { return depthOfField; }
    
    void setAspectRatio(AspectRatio r);

private:
    float       sensorWidth;
    float       sensorHeight;
    AspectRatio aspectRatio;
    // Horizontal field of view
    float       fieldOfView;
    // Distance of the sensor, deduced from the field of view
    float       focalLength;
    // Distance to the focal plane
    float       depthOfField;
};

} // namespace Graph
} // namespace Et
