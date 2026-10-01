#pragma once
#include <string>
#include <SDL3_mixer/SDL_mixer.h>

class Sound {
private:
    MIX_Audio* audio;
    MIX_Track* track;

public:
    Sound();
    Sound(std::string file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();
};