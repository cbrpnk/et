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
    Camera(Obj& obj, AspectRatio apectRatio, float aov);
    
    virtual void update() override {}
    
    float getAngleOfView()  const { return angleOfView; }
    float getFocalLength()  const { return focalLength; }
    float getSensorWidth()  const { return sensorWidth; }
    float getSensorHeight() const { return sensorHeight; }
    
    void setAspectRatio(AspectRatio r);

private:
    float       sensorWidth;
    float       sensorHeight;
    AspectRatio aspectRatio;
    float       angleOfView;
    float       focalLength;
};

} // namespace Graph
} // namespace Et
