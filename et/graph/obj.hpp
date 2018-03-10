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
    
    virtual ~Obj() {
        for(auto& c : components) {
            delete c;
        }
    }
    
    void update();
    
    unsigned int getId()          { return id; }
    bool isActive()               { return active; }
    void setActive(bool newValue) { active = newValue; }
    
    // Components
    template <typename T, typename... Ts>
    void addComponent(Ts&&... args)
    {
        if(!getComponent<T>()) components.push_back(new T(*this, args...));
    }
    
    template <typename T>
    T* getComponent() const
    {
        for(auto& c : components) {
            if(dynamic_cast<T*>(c)) return static_cast<T*>(c);
        }
        return nullptr;
    }
    
public: // TODO DEBUG ONLY: Put me back to private
    Scene& scene;
    unsigned int id;
    bool active = true;
    std::vector<Component*> components;
};

} // namespace graph
} // namespace et
