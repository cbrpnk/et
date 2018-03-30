#pragma once

namespace Et {
namespace Graph {

typedef Math::Vec3<float>         RgbFloat;
typedef Math::Vec4<float>         RgbaFloat;
typedef Math::Vec3<unsigned char> RgbByte;
typedef Math::Vec4<unsigned char> RgbaByte;

template <typename T>
class PixelBuffer {
public:
    PixelBuffer(unsigned int width, unsigned int height)
        : width(width)
        , height(height)
    {}
    
    exportPpm(std::string filePath);
   
private: 
    unsigned int width;
    unsigned int height;
    std::vector<T> buffer;
};

} // namespace Graph
} // namespace Et
