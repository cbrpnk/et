#include "camera.hpp"

#include "graph/obj.hpp"
#include "transform.hpp"

namespace Et {
namespace Graph {
    
Camera::Camera(Obj& obj, AspectRatio aspectRatio, float fov, float focalLength,
               float aperture)
    : Component(obj)
    , aspectRatio_(aspectRatio)
    , fieldOfView_(fov)
    , focalLength_(focalLength)
    , aperture_(aperture)
{
    if(!obj.getComponent<Transform>()) {
        obj.addComponent<Transform>();
    }
    
    focalPlane_.width = 2.0f * tan(Math::degToRad(fieldOfView_)/2.0f) * focalLength_;
    focalPlane_.height = focalPlane_.width * (aspectRatio_.height/aspectRatio_.width);
}

} // namespace Graph
} // namespace Et
