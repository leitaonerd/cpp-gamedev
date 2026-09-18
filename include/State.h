#pragma once
#include <vector>
#include <memory>
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

class State {
    private:
        //substituir o background antigo
        std::vector<std::unique_ptr<GameObject>> objectArray;
        Music music;
        bool quitRequested;

    public:
        //Construtor
        State();
        ~State();

        //Metodos
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void AddObject(GameObject* go);
};