#include <string>
#include <SDL3/SDL.h>

class Sprite{
    private:
        SDL_Texture* texture;
        float width;
        float height;
        SDL_FRect clipRect;

    public:
        Sprite();
        Sprite(std::string file);
        ~Sprite();

        void Open(std::string file);
        void SetClip(float x, float y, float w, float h);
        void Render(float x, float y);

        float GetWidth();
        float GetHeight();
        bool IsOpen();

};