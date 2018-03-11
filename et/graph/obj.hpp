#pragma once

#include <memory>
#include "components/component.hpp"
#include "../math/vec3.hpp"

namespace Et {
namespace Graph {

class Scene;

class Obj {
private:
    // Keep track of the last issued id in order for every object to have a unique id
    static unsigned int nextId;

public:
    Obj(Obj& other) = delete;
    Obj(Obj&& other) = delete;
    
    Obj(Scene& scene);
    
    void update();
    
    unsigned int getId()          { return id; }
    bool isActive()               { return active; }
    void setActive(bool newValue) { active = newValue; }
    
    // Components
    template <typename T, typename... Ts>
    void addComponent(Ts&&... args)
    {
        if(!getComponent<T>()) {
            components.push_back(std::move(std::make_unique<T>(*this, args...)));
        }
    }
    
    template <typename T>
    T* getComponent() const
    {
        for(auto& c : components) {
            auto p = c.get();
            if(dynamic_cast<T*>(p)) return static_cast<T*>(p);
        }
        return nullptr;
    }
    
public: // TODO DEBUG ONLY: Put me back to private
    Scene& scene;
    unsigned int id;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
};

} // namespace graph
} // namespace et
