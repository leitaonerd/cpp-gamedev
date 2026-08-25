#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

int main(int argc, char* argv[]) {
    std::cout << "Starting SDL3 linking test..." << std::endl;

    // Test standard SDL3
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "SDL3 Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "1. SDL3 initialized successfully!" << std::endl;

    // Test SDL3_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL3_ttf Init failed." << std::endl;
    } else {
        std::cout << "2. SDL3_ttf initialized successfully!" << std::endl;
        TTF_Quit();
    }

    // Clean up core SDL3
    SDL_Quit();
    
    std::cout << "All libraries linked and ran perfectly!" << std::endl;
    return 0;
}