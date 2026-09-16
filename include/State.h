#pragma once
#include "Sprite.h"
#include "Music.h"

class State {
    private:
        //Atributos
        Sprite bg;
        Music music;
        bool quitRequested;

    public:
        //Construtor
        State();

        //Metodos
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};