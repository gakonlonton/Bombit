#ifndef GAME_H_
#define GAME_H_

#include "include/System/KeyboardInput.h"
#include "include/Display/DisplayManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Game {
    public:
        Game();
        bool loadImage();
        int onExecute();
        bool Init();
        void onEvent(SDL_Event* Event);
        void onLoop();
        void onRender();
        void gameCleanup();
    protected:
    private:
        bool RunningGame;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event Event;
        KeyboardInput* keyboardInput;
        SDL_Texture* texture;
        DisplayManager* display_manager;

        unsigned int windowWidth;
        unsigned int windowHeight;
};

#endif // GAME_H_
