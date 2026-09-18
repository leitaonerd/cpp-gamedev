#pragma once
#include "Component.h"
#include "Sprite.h"
#include <string>

class SpriteRenderer : public Component {
private:
    Sprite sprite;

public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
    
    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void SetFrame(int frame);
    
    //overide dos métodos abstratos
    void Update(float dt) override;
    void Render() override;
};