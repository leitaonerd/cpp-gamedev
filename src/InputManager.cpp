#include "InputManager.h"

//singleton
InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() : quitRequested(false), updateCounter(0), mouseX(0), mouseY(0) {
    for (int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    } //só tem 5 botoes principais na SDL3
}

InputManager::~InputManager() {
}

void InputManager::Update() {
    SDL_Event event;

    float fX, fY;
    SDL_GetMouseState(&fX, &fY);
    mouseX = static_cast<int>(fX);
    mouseY = static_cast<int>(fY);

    quitRequested = false;
    updateCounter++;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            quitRequested = true;
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            int button = event.button.button;
            mouseState[button] = (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN);
            mouseUpdate[button] = updateCounter;
        }

        else if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
            // ignora o auto-repeat quando segura tecla
            if (!event.key.repeat) {
                // Em SDL3 a tecla é acessada via event.key.key (em SDL2 era event.key.keysym.sym)
                int key = event.key.key;
                
                // unordered_map cria o elemento automaticamente se não existir
                keyState[key] = (event.type == SDL_EVENT_KEY_DOWN);
                keyUpdate[key] = updateCounter;
            }
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}