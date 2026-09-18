#include "Animator.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Animator::Animator(GameObject& associated) 
    : Component(associated), frameStart(0), frameEnd(0), frameTime(0.0f), currentFrame(0), timeElapsed(0.0f) {
}

void Animator::Update(float dt) {
    //se frameTime for 0, não tem animação
    if (frameTime == 0.0f) {
        return; 
    }

    timeElapsed += 1.0f; //mudar depois pelo delta time de vdd

    //passou mais tempo que o tempo do frame
    if (timeElapsed > frameTime) {
        currentFrame++;
        timeElapsed -= frameTime;

        //passou do ultimo quadro
        if (currentFrame > frameEnd) {
            currentFrame = frameStart;
        }

        //atualiza o frame no SpriteRenderer do mesmo objeto
        SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
        if (sprite != nullptr) {
            sprite->SetFrame(currentFrame);
        }
    }
}

void Animator::Render() {
}

void Animator::SetAnimation(std::string name) {
    auto it = animations.find(name);
    if (it != animations.end()) {
        frameStart = it->second.frameStart;
        frameEnd = it->second.frameEnd;
        frameTime = it->second.frameTime;

        currentFrame = frameStart;
        timeElapsed = 0.0f;

        //chama SetFrame no SpriteRenderer
        SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
        if (sprite != nullptr) {
            sprite->SetFrame(currentFrame);
        }
    }
}

void Animator::AddAnimation(std::string name, Animation anim) {
    //insere o par se não encontrar a animação no mapa
    if (animations.find(name) == animations.end()) {
        animations[name] = anim; 
    }
}