#ifndef PAUSE_DISPLAY_H
#define PAUSE_DISPLAY_H

#include "Display.h"
#include <SDL.h>
#include <vector>

using namespace std;

class PauseDisplay : public Display {
    public:
        PauseDisplay(SDL_Renderer* renderer,
                     int windowWidth, int windowHeight,
                     Display* previousDisplay = nullptr);

        ~PauseDisplay();
        PauseDisplay(const PauseDisplay& other) = delete;
        PauseDisplay& operator=(const PauseDisplay&) = delete;

        void Init();
        void Enter(int mode = 0);
        void Leave();
        int Destroy();
        void Update();
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        SDL_Renderer* d_renderer;
        vector<SDL_Texture*> d_textures;
        vector<SDL_Rect> d_textures_draw_src;
        vector<SDL_Rect> d_textures_draw_dest;
        SDL_Texture* d_arrowTexture;
        int d_arrowHeight, d_arrowWidth, d_arrow;
        bool d_buttonPressedDown, d_buttonPressedUp, d_buttonPressedEnter;
        int d_windowWidth, d_windowHeight;
        bool d_quit;
        Display* d_previousDisplay;
};

#endif // PAUSE_DISPLAY_H

