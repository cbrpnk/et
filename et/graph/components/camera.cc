#include "camera.hpp"

namespace Et {
namespace Graph {
    
Camera::Camera(Obj& obj, AspectRatio aspectRatio, float fov, float dof)
    : Component(obj)
    , fieldOfView(fov)
    , depthOfField(dof)
{
    setAspectRatio(aspectRatio);
}

void Camera::setAspectRatio(AspectRatio r)
{
    aspectRatio = r;
    sensorWidth = 1.0f;
    
    if(r == AspectRatio::R11) {
        sensorHeight = 1.0f;
    } else if(r == AspectRatio::R21) {
        sensorHeight = 1.0f/2.0f;
    } else if(r == AspectRatio::R43) {
        sensorHeight = 3.0f/4.0f;
    } else if(r == AspectRatio::R169) {
        sensorHeight = 9.0f/16.0f;
    }
    
    focalLength = (sensorWidth/(2.0f*tan(Math::degToRad(fieldOfView)/2)));
}

} // namespace Graph
} // namespace Et
