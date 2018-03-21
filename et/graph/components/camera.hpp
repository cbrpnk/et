#ifndef ET_GRAPH_COMPONENT_CAMERA_HPP
#define ET_GRAPH_COMPONENT_CAMERA_HPP

#include <iostream>
#include "component.hpp"
#include "../../math/functions.hpp"

namespace Et {
namespace Graph {

class Obj;

class Camera : public Component {
public:
    enum class AspectRatio {
        R1_1,
        R2_1,
        R4_3,
        R16_9
    };

public:
    Camera(Obj& obj, AspectRatio apectRatio, float aov)
        : Component(obj)
        , angleOfView(aov)
    {
        setAspectRatio(aspectRatio);
    }
    
    virtual ~Camera() override {}
    
    virtual void update() override {}
    
    float getAngleOfView()  const { return angleOfView; }
    float getFocalLength()  const { return focalLength; }
    float getSensorWidth()  const { return sensorWidth; }
    float getSensorHeight() const { return sensorHeight; }
    
    void setAspectRatio(AspectRatio r) {
        aspectRatio = r;
        sensorWidth = 1.0f;
        
        switch(r) {
        case AspectRatio::R1_1:
            sensorHeight = 1.0f;
            break;
        case AspectRatio::R2_1:
            sensorHeight = 1.0f/2.0f;
            break;
        case AspectRatio::R4_3:
            sensorHeight = 3.0f/4.0f;
            break;
        case AspectRatio::R16_9:
            sensorHeight = 9.0f/16.0f;
            break;
        }
        
        focalLength = (sensorWidth/(2.0f*tan(Math::degToRad(angleOfView)/2)));
    }

private:
    float       sensorWidth;
    float       sensorHeight;
    AspectRatio aspectRatio;
    float       angleOfView;
    float       focalLength;
};

} // namespace Graph
} // namespace Et

#endif
