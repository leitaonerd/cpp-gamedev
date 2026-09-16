#pragma once

//forward declaration para evitar inclusão circular
class GameObject;

class Component {
protected:
    GameObject& associated;

public:
    //recebe a referência e a iniciasliza na lista
    Component(GameObject& associated) : associated(associated) {}
    
    //obs: perguntar se pode usar destructor virtual
    virtual ~Component() = default; 

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};