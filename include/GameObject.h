#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Component.h"
#include "Rect.h"

class GameObject {
private:
    std::vector<Component*> components;
    bool isDead;

public:
    Rect box;

    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);

    //implementação do template para retornar o tipo certo
    template<typename T>
    T* GetComponent() {
        for (int i = 0; i < components.size(); i++) {
            T* component = dynamic_cast<T*>(components[i]);
            if (component != nullptr) {
                return component;
            }
        }
        return nullptr;
    }
};