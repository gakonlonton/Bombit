#include <bits/stdc++.h>
#include "game.h"

using namespace std;

bool Game::Init(void) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }
    // Window Init
    window = SDL_CreateWindow("BOMBIT", 50, 50,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        return false;
    }
    // Renderer Init
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        cout << SDL_GetError() << "\n";
        return false;
    }
    // TTF Init
    if(TTF_Init() != 0) {
        cout << "TTF_Init Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return true;
    }
    return true;
}

void Game::onRender() {
    SDL_RenderClear(renderer);
    display_manager->Draw(renderer);
    SDL_RenderPresent(renderer);
    return;
}

void Game::onLoop(void) {
    display_manager->Update();
    return;
}
