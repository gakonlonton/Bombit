#include "../../include/Constant/Resources.h"
#include "../../include/Display/Loading.h"
#include "../../include/System/TextRenderer.h"
#include "../../include/Display/DisplayGame.h"

#include <bits/stdc++.h>

using namespace std;

Loading::Loading(SDL_Texture* texture, SDL_Renderer* renderer, int windowWidth, int windowHeight)
    : Display(),
      d_texture(texture),
      d_renderer(renderer),
      d_windowWidth(windowWidth),
      d_windowHeight(windowHeight),
      m_timer(),
      m_game_over(false),
      m_music(nullptr),
      m_musicWait(RESOURCE_MUSIC_LOAD_TIME) {

    string path_music = RESOURCE_BASE + RESOURCE_MUSIC_LOAD;
    m_music = Mix_LoadMUS(path_music.c_str());
}

Loading::~Loading() {
    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }

    d_textures.clear();
    d_textures_draw_src.clear();
    d_textures_draw_dest.clear();
}

void Loading::Init() {
    Mix_PlayMusic(m_music, -1);
}

void Loading::Enter(int mode) {
    Mix_PlayMusic(m_music, -1);
    d_nextDisplay = nullptr;
    d_leavePrevious = false;
    d_leaveNext = false;
    m_timer.Unpause();
    m_timer.ResetTimer();
    if(mode == 0) {
        MakeTexture("GAME OVER");
        m_game_over = true;
    }
    else {
        MakeTexture("GAME COMPLETED");
        m_game_over = true;
    }
}

void Loading::Leave() {
    Mix_HaltMusic();
    DestroyTextures();
}

int Loading::Destroy() {
    Mix_HaltMusic();
    Mix_FreeMusic(m_music);
    DestroyTextures();
    return 0;
}

void Loading::DestroyTextures() {
    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }

    d_textures.clear();
    d_textures_draw_src.clear();
    d_textures_draw_dest.clear();
}

void Loading::Update() {
    if(d_nextDisplay == nullptr && m_game_over == false) {
        d_nextDisplay = new GameDisplay(d_texture, d_renderer, d_windowWidth, d_windowHeight);
    }
    else if(m_timer.GetTimeElapsed() > m_musicWait)  {
        if(m_game_over) {
            d_leavePrevious = true;
        }
        else d_leaveNext = true;
    }
}

void Loading::Draw(SDL_Renderer* renderer) const {
    for(unsigned int i = 0; i < (int) d_textures.size(); i++) {
        SDL_RenderCopy(renderer, d_textures[i], &d_textures_draw_src[i], &d_textures_draw_dest[i]);
    }
}

void Loading::MakeTexture(string text) {
    string path_font = RESOURCE_BASE + RESOURCE_FONT;
    TextRenderer text_renderer(path_font, 96);

    SDL_Color color = {0, 0, 200, 255};
    SDL_Rect SrcR = {0, 0, 0, 0};
    SDL_Rect DestR = {0, 0, 0, 0};
    SDL_Texture* image;

    image = text_renderer.RenderText(text, color, d_renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = d_windowWidth/2 -  SrcR.w/2;
    DestR.y = d_windowHeight/2 - SrcR.h/2;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);
}

