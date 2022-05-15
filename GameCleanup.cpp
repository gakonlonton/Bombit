#include "game.h"

using namespace std;

void Game::gameCleanup(void) {
//    delete display_manager;
    Mix_CloseAudio();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
