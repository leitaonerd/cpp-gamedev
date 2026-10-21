#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Camera.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) 
    : Component(associated) {
}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH) 
    : Component(associated), sprite(file, frameCountW, frameCountH) {
    
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    
    SetFrame(0);
}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    //atualiza as dimensoes sempre q abre outro arquivo
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetFrame(int frame, SDL_FlipMode flip) {
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    Vec2 center = associated.box.Center(); 
    
    sprite.SetScale(scaleX, scaleY); 
    
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    
    associated.box.x = center.x - (associated.box.w / 2.0f);
    associated.box.y = center.y - (associated.box.h / 2.0f);
}

void SpriteRenderer::Update(float dt) {
}

void SpriteRenderer::SetCameraFollower(bool follow) {
    sprite.SetCameraFollower(follow);
}

void SpriteRenderer::Render() {
    //repassa cordenada e dimensoes pro render do sprite
    sprite.Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h, associated.angleDeg);
}