#ifndef PLAYERS_NUMBER_H
#define PLAYERS_NUMBER_H

#include "Display.h"
#include <vector>

using namespace std;

class PlayersNumber : public Display {
    public:
        PlayersNumber(SDL_Renderer* renderer, int window_width, int window_height);

        ~PlayersNumber();
        PlayersNumber(const PlayersNumber& other) = delete;
        PlayersNumber& operator=(const PlayersNumber&) = delete;

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
        vector<SDL_Rect> d_textures_draw_src, d_textures_draw_dest;
        SDL_Texture* d_arrowTexture;
        int d_arrowHeight, d_arrowWidth, d_arrow;
        bool d_buttonPressedDown, d_buttonPressedUp, d_buttonPressedEnter;
        int d_windowWidth, d_windowHeight, m_players_selected;
};

#endif // PLAYERS_NUMBER_H

