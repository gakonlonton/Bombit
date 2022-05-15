#include <bits/stdc++.h>
#include "game.h"
#include "include/Constant/WindowConstant.h"

using namespace std;

Game::Game(void)
    : RunningGame(true), Event(), keyboardInput(KeyboardInput::Instance()),
      window(nullptr), renderer(nullptr), texture(nullptr), display_manager(nullptr),
      windowWidth(WINDOW_WIDTH), windowHeight(WINDOW_HEIGHT) {}

int Game::onExecute(void) {
    if(!Init()) return -1;
    if(!loadImage()) return -1;
    while(RunningGame) {
        while(SDL_PollEvent(&Event)) {
            onEvent(&Event);
        }
        onLoop();
        onRender();
    }
    gameCleanup();
    return 0;
}

int main(int argc, char* args[]) {
    Game BOMBIT;
    return BOMBIT.onExecute();
}

