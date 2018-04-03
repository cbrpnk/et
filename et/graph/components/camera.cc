#include "camera.hpp"

namespace Et {
namespace Graph {
    
Camera::Camera(Obj& obj, AspectRatio aspectRatio, float fov, float dof)
    : Component(obj)
    , fieldOfView_(fov)
    , depthOfField_(dof)
{
    setAspectRatio(aspectRatio);
}

void Camera::setAspectRatio(AspectRatio r)
{
    aspectRatio_ = r;
    sensorWidth_ = 1.0f;
    
    if(r == AspectRatio::R11) {
        sensorHeight_ = 1.0f;
    } else if(r == AspectRatio::R21) {
        sensorHeight_ = 1.0f/2.0f;
    } else if(r == AspectRatio::R43) {
        sensorHeight_ = 3.0f/4.0f;
    } else if(r == AspectRatio::R169) {
        sensorHeight_ = 9.0f/16.0f;
    }
    
    focalLength_ = (sensorWidth_/(2.0f*tan(Math::degToRad(fieldOfView_)/2)));
}

} // namespace Graph
} // namespace Et
