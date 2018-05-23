#pragma once

namespace Et {
namespace Graph {

struct Mesh {
    Mesh() {}
    
    Mesh(const Mesh& other)
    {
        indices = other.indices;
        vertices = other.vertices;
        normals = other.normals;
        colors = other.colors;
    }
    
    std::vector<unsigned short> indices;
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> colors;
};

} // namespace graph
} // namespace et
