#ifndef LOADING_H
#define LOADING_H

#include <bits/stdc++.h>
#include "Display.h"
#include "../System/FreeTimer.h"
#include <SDL.h>

using namespace std;

class Loading : public Display {
    public:
        Loading(SDL_Texture* texture, SDL_Renderer* renderer, int windowWidth, int windowHeight);

        ~Loading();
        Loading(const Loading& other) = delete;
        Loading& operator=(const Loading&) = delete;

        void Init();
        void Enter(int mode);
        void Leave();
        int Destroy();
        void Update();
        void Draw(SDL_Renderer* renderer) const;

    protected:

        void MakeTexture(string text);
        void DestroyTextures();

    private:
        SDL_Texture* d_texture;
        SDL_Renderer* d_renderer;
        vector<SDL_Texture*> d_textures;
        vector<SDL_Rect> d_textures_draw_src, d_textures_draw_dest;
        int d_windowWidth, d_windowHeight;
        FreeTimer m_timer;
        bool m_game_over;
        Mix_Music* m_music;
        int m_musicWait;
};

#endif // LOADING_H

