#pragma once

#include <memory>
#include "component.hpp"
#include "graph/ray.hpp"
#include "graph/mesh.hpp"

namespace Et {
namespace Graph {

class Obj;

class Geometry : public Component {
public:
    Geometry(Obj& obj)
        : Component(obj)
        , hasMesh_{false}
        , mesh_{nullptr}
    {}
    virtual HitRecord intersect(Ray ray) const = 0;
    
    virtual void update() override {}
    
    Mesh* getMesh() { return mesh_.get(); }
    void addMesh(const Mesh& newMesh)
    {
        mesh_ = std::make_shared<Mesh>(newMesh);
        hasMesh_ = true;
    }
    
private:
    bool hasMesh_;
    std::shared_ptr<Mesh> mesh_;
};

}} // namespace Et::Graph
