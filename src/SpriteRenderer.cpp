#include "SpriteRenderer.h"
#include "GameObject.h"

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

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::Update(float dt) {
}

void SpriteRenderer::Render() {
    //repassa cordenada e dimensoes pro render do sprite
    sprite.Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}