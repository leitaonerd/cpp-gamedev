#pragma once
#include <SDL3/SDL.h>

class Animation {
public:
    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_FlipMode flip;

    Animation(int frameStart = 0, int frameEnd = 0, float frameTime = 0.0f) 
        : frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime), flip(SDL_FLIP_NONE) {}
};