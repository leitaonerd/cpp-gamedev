#include "Sprite.h"
#include "Game.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

Sprite::Sprite() : texture(nullptr), width(0), height(0), frameCountW(1), frameCountH(1) {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) : texture(nullptr){
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    Open(file);
}

Sprite::~Sprite(){
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file){
    if (texture){
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
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

void Sprite::Render(float x, float y, float w, float h){
    if (texture){
        SDL_FRect dstRect = { x, y, w, h };
        //passa o clipRect como a origem e dstRect como o destino
        SDL_RenderTexture(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
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

float Sprite::GetWidth(){
    return width / frameCountW;
}

float Sprite::GetHeight(){
    return height / frameCountH;
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}