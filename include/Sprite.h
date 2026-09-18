#pragma once
#include <string>
#include <SDL3/SDL.h>

class Sprite{
    private:
        SDL_Texture* texture;
        float width;
        float height;
        SDL_FRect clipRect;

        int frameCountW;
        int frameCountH;

    public:
        Sprite();
        Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
        ~Sprite();

        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render(float x, float y, float w, float h);

        float GetWidth();
        float GetHeight();
        bool IsOpen();

        void SetFrame(int frame);
        void SetFrameCount(int frameCountW, int frameCountH);

};