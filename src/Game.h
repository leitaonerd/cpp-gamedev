#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include "State.h"

class Game {
    private:
        //Atributos
        static Game* instance;

        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        MIX_Mixer* mixer;

        //Construtor
        Game(std::string title, int width, int height);

    public:
        //Destructor
        ~Game();

        //Metodos
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        MIX_Mixer* GetMixer();

        static Game& GetInstance();
};