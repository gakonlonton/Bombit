#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <bits/stdc++.h>
#include "Display.h"
#include "SDL.h"

using namespace std;

class DisplayManager {
    public:
        DisplayManager(SDL_Texture* texture, SDL_Renderer* renderer,
                       bool* running,
                       int windowWidth, int windowHeight);
        ~DisplayManager();
        DisplayManager(const DisplayManager& other) = delete;
        DisplayManager& operator=(const DisplayManager&) = delete;

        void Update(void);
        void Draw(SDL_Renderer* renderer);

    protected:
        void EnterDisplay(Display* display);
        void LeaveDisplay();
        Display* CurrentDisplay();
    private:
        stack<Display*> s_displays;
        SDL_Renderer* s_renderer;
        int s_windowWidth;
        int s_windowHeight;
};

#endif // DISPLAY_MANAGER_H
