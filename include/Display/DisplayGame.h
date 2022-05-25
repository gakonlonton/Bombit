#ifndef DISPLAY_GAME_H
#define DISPLAY_GAME_H

#include "../../include/Display/Display.h"
#include "DisplayElement.h"
#include "../System/Relay.h"
#include <bits/stdc++.h>

using namespace std;


class GameDisplay : public Display {
    public:
        GameDisplay(SDL_Texture* texture, SDL_Renderer* renderer,
                    int windowWidth, int windowHeight, int players_number, int current_level, int number_of_screen_elements = 6);

        ~GameDisplay();
        GameDisplay(const GameDisplay& other) = delete;
        GameDisplay& operator=(const GameDisplay&) = delete;

        void AddDisplayElement(DisplayElement* display_element);
        void Init();
        void Enter(int mode = 0);
        void Leave();
        int Destroy();
        void Update();
        void Draw(SDL_Renderer* renderer) const;
    protected:

    private:
        vector<DisplayElement*> d_displayElements;
        Relay* m_relay;
        SDL_Texture* d_texture;
        SDL_Renderer* d_renderer;
        int d_windowWidth, d_windowHeight, m_players_number, d_current_level;
        bool d_level_completed, m_play_music = true;
        Mix_Music* m_music;
};

#endif // DISPLAY_GAME_H
