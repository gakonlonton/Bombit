#include "game.h"

using namespace std;

void Game::onEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        RunningGame = false;
    }
    switch(Event->type) {
        case SDL_KEYDOWN:
            keyboardInput->TurnKeyOn(Event->key.keysym.sym);
            break;
        case SDL_KEYUP:
            keyboardInput->TurnKeyOff(Event->key.keysym.sym);
            switch(Event->key.keysym.sym) {
                case SDLK_0:
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return;
}

