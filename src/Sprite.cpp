#include "Sprite.h"
#include "Game.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

Sprite::Sprite(){
    texture = nullptr;
}

Sprite::Sprite(std::string file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    if (IsOpen()) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if (IsOpen()) {
        SDL_DestroyTexture(texture);
    }
    
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    texture = IMG_LoadTexture(renderer, file.c_str());
    
    if (texture == nullptr) {
        std::cerr << "Erro IMG_LoadTexture: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_GetTextureSize(texture, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(float x, float y, float w, float h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(float x, float y) {
    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    
    SDL_FRect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;
    
    SDL_RenderTexture(renderer, texture, &clipRect, &dstRect);
}

float Sprite::GetWidth() {
    return width;
}

float Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}