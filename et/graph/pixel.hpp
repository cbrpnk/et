#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "color.hpp"

namespace Et {
namespace Graph {

// A Collection of pixels, more commonly known as an image
template <typename T>
class PixelBuffer {
public:
    PixelBuffer(unsigned int width, unsigned int height)
        : width(width)
        , height(height)
        , buffer(width * height)
    {}
    
    T& operator()(unsigned int x, unsigned int y)
    {
        return buffer[y*width+x];
    }
    
    virtual void exportPpm(std::string filePath) = 0;
   
protected: 
    unsigned int width;
    unsigned int height;
    std::vector<T> buffer;
};

template <typename T>
class RgbBuffer : public PixelBuffer<RgbColor<T>> {
public:
    RgbBuffer(unsigned int width, unsigned int height)
        : PixelBuffer<RgbColor<T>>(width, height)
    {}
    
    virtual void exportPpm(std::string filePath) override;
};

template <typename T>
void RgbBuffer<T>::exportPpm(std::string filePath) {
    std::ofstream file;
    file.open(filePath.c_str());
    file << "P6 " << this->width << " " << this->height << " 255\n";
    for(unsigned int y=0; y<this->height; ++y) {
        for(unsigned int x=0; x<this->width; ++x) {
            RgbColor<T>& pixel = (*this)(x, y);
            file << (unsigned char) (sqrt(pixel.r()) * 255);
            file << (unsigned char) (sqrt(pixel.g()) * 255);
            file << (unsigned char) (sqrt(pixel.b()) * 255);
        }
    }
    file.close();
}

} // namespace Graph
} // namespace Et
