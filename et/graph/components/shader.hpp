#pragma once

#include "GL/gl.h"

namespace Et {
namespace Graph {

class Obj;

class ShaderProgram : public Component {
public:
    ShaderProgram(Obj& obj)
        : Component(obj)
    {}
    
    void addVertexShader(std::string path);
    void addFragmentShader(std::string path);
    
    void Compile();
    void Link();
    void Validate();
    
private:
    unsigned int shaderProgramId;
};

}} // namespace Et::Graph
