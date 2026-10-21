#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

Sprite::Sprite() : texture(nullptr), width(0), height(0), frameCountW(1), frameCountH(1), cameraFollower(false), scale(1.0f, 1.0f), flip(SDL_FLIP_NONE) {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) : texture(nullptr), cameraFollower(false), scale(1.0f, 1.0f), flip(SDL_FLIP_NONE){
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    this->cameraFollower = false;
    Open(file);
}

Sprite::~Sprite(){
    if(texture){
        //SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file){
    texture = Resources::GetImage(file);
    if (texture == nullptr){
        std::cerr << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
        return;
    }

    //SDL_QueryTexture foi substituído por obter as propriedades via float
    float fWidth, fHeight;
    SDL_GetTextureSize(texture, &fWidth, &fHeight);
    width = static_cast<int>(fWidth);
    height = static_cast<int>(fHeight);

    SetFrame(0); //0 eh padrao
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x = static_cast<float>(x);
    clipRect.y = static_cast<float>(y);
    clipRect.w = static_cast<float>(w);
    clipRect.h = static_cast<float>(h);
}

void Sprite::SetCameraFollower(bool follow) {
    cameraFollower = follow;
}

void Sprite::Render(float x, float y, float w, float h, double angle){
    if (texture){
        //subtrai a camera para nao seguir
        float renderX = x - (cameraFollower ? 0 : Camera::pos.x);
        float renderY = y - (cameraFollower ? 0 : Camera::pos.y);

        SDL_FRect dstRect = { renderX, renderY, w, h };
        SDL_RenderTextureRotated(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, angle, nullptr, flip);
    }
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH){
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
}

void Sprite::SetFrame(int frame) {
    int frameW = GetWidth();
    int frameH = GetHeight();
    
    int currentX = (frame % frameCountW) * frameW;
    int currentY = (frame / frameCountW) * frameH;
    
    SetClip(currentX, currentY, frameW, frameH);
}

float Sprite::GetWidth() {
    return (width / frameCountW) * scale.x;
}

float Sprite::GetHeight() {
    return (height / frameCountH) * scale.y;
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0) {
        scale.x = scaleX;
    }
    if (scaleY != 0) {
        scale.y = scaleY;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::SetFlip(SDL_FlipMode f) {
    flip = f;
}