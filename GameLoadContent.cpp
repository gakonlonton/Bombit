#include <bits/stdc++.h>
#include "game.h"
#include "SDL_image.h"
#include "include/Display/DisplayManager.h"
#include "include/Constant/Resources.h"

using namespace std;

bool Game::loadImage(void) {
    string path = "resources\\textures.bmp";
    SDL_Surface* loadedSF = IMG_Load(path.c_str());
    if(loadedSF == nullptr) {
        cout << "Unable to load image " << path << " SDL_image: Error: " << IMG_GetError() << "\n";
        return false;
    }
    else {
        SDL_SetColorKey(loadedSF, SDL_TRUE, SDL_MapRGB(loadedSF->format, 0, 0xC0, 0xC0));
        texture = SDL_CreateTextureFromSurface(renderer, loadedSF);
        SDL_FreeSurface(loadedSF);
        if(texture == nullptr) {
            cout << "Unable to create texture from " << path << " SDL: Error: "
                 << SDL_GetError() << "\n";
            return false;
        }
        display_manager = new DisplayManager(texture, renderer, &RunningGame, windowWidth, windowHeight);
    }
    return true;
}
