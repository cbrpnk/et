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
    
    virtual ~Obj() {}
    
    void update();
    
    unsigned int getId()           { return id; }
    bool isActive()                { return active; }
    void setActive(bool newValue)  { active = newValue; }
    
    // Components
    template <typename T>
    void addComponent()
    {
        if(!getComponent<T>()) components.push_back(std::make_unique<T>());
    }
    
    template <typename T, typename T2, typename... Ts>
    void addComponent()
    {
        addComponent<T>();
        addComponent<T2, Ts...>();
    }
    
    template <typename T>
    T* getComponent() const
    {
        for(auto& componentPtr : components) {
            Component* c =  componentPtr.get();
            if(dynamic_cast<T*>(c)) return static_cast<T*>(c);
        }
        return nullptr;
    }
    
    
    
private:
    Scene& scene;
    unsigned int id;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
};

} // namespace graph
} // namespace et
