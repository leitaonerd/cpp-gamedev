#include "Camera.h"
#include "InputManager.h"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if(focus != nullptr) {
        pos.x = focus->box.Center().x - 600.0f;
        pos.y = focus->box.Center().y - 450.0f;
    } 
    else{
        InputManager& input = InputManager::GetInstance();
        
        float camSpeed = 300.0f; 
        
        speed = Vec2(0, 0);

        if(input.IsKeyDown(LEFT_ARROW_KEY)){
            speed.x = -camSpeed;
        }
        if(input.IsKeyDown(RIGHT_ARROW_KEY)){
            speed.x = camSpeed;
        }
        if(input.IsKeyDown(UP_ARROW_KEY)){
            speed.y = -camSpeed;
        }
        if(input.IsKeyDown(DOWN_ARROW_KEY)){
            speed.y = camSpeed;
        }

        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
    }
}