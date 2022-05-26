#include <bits/stdc++.h>
#include <SDL.h>
#include "SDL_image.h"
#include "../../include/Display/DisplayUtilities.h"
#include "../../include/Constant/Resources.h"
#include "../../include/System/TextRenderer.h"
#include "../../include/Display/MainMenu.h"
#include "../../include/Display/Loading.h"

using namespace std;

SDL_Texture* load_image(string path, SDL_Renderer* renderer) {
    SDL_Texture* new_texture = nullptr;
    SDL_Surface* loadedSF = IMG_Load(path.c_str());
    new_texture = SDL_CreateTextureFromSurface(renderer, loadedSF);
    SDL_FreeSurface(loadedSF);
    return new_texture;
}

WelcomeDisplay::WelcomeDisplay(SDL_Texture* texture, SDL_Renderer* renderer, int windowWidth, int windowHeight)
    : Display(),
      d_texture(texture), d_renderer(renderer),
      d_pressedNext(false), d_pressedPrevious(false),
      d_windowWidth(windowWidth), d_windowHeight(windowHeight) {

    string path_font = RESOURCE_BASE + RESOURCE_FONT;
    TextRenderer text_renderer(path_font, 54);
    SDL_Color color = {155, 0, 255, 0};
    SDL_Rect SrcR = {0, 0, 0, 0};
    SDL_Rect DestR = {0, 0, 0, 0};
    SDL_Texture* image;

    image = load_image("resources\\menu.png", renderer);
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);

    Mix_Music* m_music;
    string path_music = RESOURCE_BASE + RESOURCE_MUSIC_MENU;
    m_music = Mix_LoadMUS(path_music.c_str());
    Mix_VolumeMusic(10);
    Mix_PlayMusic(m_music, -1);
}

WelcomeDisplay::~WelcomeDisplay() {
    Destroy();
}

void WelcomeDisplay::Enter(int tmp) {
    d_leavePrevious = true;
    d_leaveNext = false;
}

void WelcomeDisplay::Leave() {
    Destroy();
}

int WelcomeDisplay::Destroy() {
    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }
    d_textures.clear();
    d_textures_draw_src.clear();
    d_textures_draw_dest.clear();
    return 0;
}

void WelcomeDisplay::Update() {
    if(d_pressedNext and d_keyboardInput->IsKeyOn(SDLK_RETURN)) {
        d_pressedNext = false;
        d_nextDisplay = new MainMenu(d_texture, d_renderer, d_windowWidth, d_windowHeight);
        d_leaveNext = true;
    }
    if(d_pressedPrevious and d_keyboardInput->IsKeyOn(SDLK_ESCAPE)) {
        d_pressedPrevious = false;
        d_leavePrevious = true;
    }

    if(!(d_keyboardInput->IsKeyOn(SDLK_RETURN))) d_pressedNext = true;
    if(!(d_keyboardInput->IsKeyOn(SDLK_ESCAPE))) d_pressedPrevious = true;
}

void WelcomeDisplay::Draw(SDL_Renderer* renderer) const {
    for(int i = 0; i < (int) d_textures.size(); i++) {
        if(i == 0) {
            SDL_RenderCopy(renderer, d_textures[i], NULL, NULL);
        }
        else SDL_RenderCopy(renderer, d_textures[i], &d_textures_draw_src[i], &d_textures_draw_dest[i]);
    }
}
