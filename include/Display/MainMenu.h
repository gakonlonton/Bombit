#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Display.h"

class MainMenu : public Display {
    public:
        MainMenu(SDL_Texture* texture, SDL_Renderer* renderer,
                 int windowWidth, int windowHeight);

        ~MainMenu();
        MainMenu(const MainMenu& other) = delete;
        MainMenu& operator=(const MainMenu&) = delete;

        void Init();
        void Enter(int mode = 0);
        void Leave();
        int Destroy();
        void Update();
        void Draw(SDL_Renderer* renderer) const;

    protected:
    private:
        SDL_Texture* d_texture;
        SDL_Renderer* d_renderer;
        vector<SDL_Texture*> d_textures;
        vector<SDL_Rect> d_textures_draw_src, d_textures_draw_dest;
        SDL_Texture* d_arrowTexture;
        int d_arrowHeight, d_arrowWidth, d_arrow;
        bool d_buttonPressedDown, d_buttonPressedUp, d_buttonPressedEnter;
        int d_windowWidth, d_windowHeight;
        Mix_Music* m_music;

};

#endif // MAIN_MENU_H

