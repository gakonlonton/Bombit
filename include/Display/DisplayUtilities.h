#ifndef DISPLAY_UTILITY_H
#define DISPLAY_UTILITY_H

#include <bits/stdc++.h>
#include "Display.h"
#include "SDL_image.h"
#include <SDL.h>

class WelcomeDisplay : public Display {
    public:
        WelcomeDisplay(SDL_Texture* texture, SDL_Renderer* renderer, int windowWidth, int windowHeight);
        void Enter(int tmp = 0);
        void Update();
        void Leave();
        int Destroy();
        void Draw(SDL_Renderer* renderer) const;
        ~WelcomeDisplay();
        WelcomeDisplay(const WelcomeDisplay& other) = delete;
        WelcomeDisplay& operator=(const WelcomeDisplay&) = delete;
    protected:
    private:
        SDL_Texture* d_texture;
        SDL_Renderer* d_renderer;
        vector<SDL_Texture*> d_textures;
        vector<SDL_Rect> d_textures_draw_src, d_textures_draw_dest;
        bool d_pressedNext, d_pressedPrevious;
        int d_windowWidth, d_windowHeight;
};

SDL_Texture* load_image(string path, SDL_Renderer* renderer);

#endif // DISPLAY_UTILITY_H
