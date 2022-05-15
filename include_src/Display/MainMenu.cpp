#include "../../include/Display/MainMenu.h"
#include "../../include/System/TextRenderer.h"
#include "../../include/Constant/Resources.h"
#include "../../include/Display/Loading.h"

using namespace std;

MainMenu::MainMenu(SDL_Texture* texture, SDL_Renderer* renderer,
                   int windowWidth, int windowHeight)
    : Display(),
      d_texture(texture),
      d_renderer(renderer),
      d_arrow(0),
      d_buttonPressedDown(false),
      d_buttonPressedUp(false),
      d_buttonPressedEnter(false),
      d_windowWidth(windowWidth),
      d_windowHeight(windowHeight),
      m_music(nullptr) {

    string path_font = RESOURCE_BASE + RESOURCE_FONT;
    TextRenderer text_renderer(path_font, 64);

    SDL_Color color = {255, 255, 255, 0};
    SDL_Rect SrcR = {0, 0, 0, 0};
    SDL_Rect DestR = {0, 0, 0, 0};
    SDL_Texture* image;

    image = text_renderer.RenderText("NEW GAME", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = windowWidth/2 -  SrcR.w/2;
    DestR.y = windowHeight/2 - SrcR.h/2 - SrcR.h;
    DestR.h = SrcR.h; DestR.w = SrcR.w;

    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("EXIT", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.y += SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);

    d_arrowTexture = text_renderer.RenderText(">", color, renderer);
    SDL_QueryTexture(d_arrowTexture, NULL, NULL, &d_arrowWidth, &d_arrowHeight);

    string path_music = RESOURCE_BASE + RESOURCE_MUSIC_MENU;
    m_music = Mix_LoadMUS(path_music.c_str());
}

#define corner d_textures.size()

MainMenu::~MainMenu(void) {
    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }

    SDL_DestroyTexture(d_arrowTexture);
    d_textures.clear();
    d_textures_draw_dest.clear();
    d_textures_draw_src.clear();
}

void MainMenu::Init(void) {
    Mix_PlayMusic(m_music, -1);
    Enter();
}

void MainMenu::Enter(int mode) {

    d_leaveNext = false;
    d_leavePrevious = false;
    d_arrow = 0;
    d_buttonPressedDown = false;
    d_buttonPressedUp = false;
    d_buttonPressedEnter = false;
}

void MainMenu::Leave(void) {
    Mix_HaltMusic();
}

int MainMenu::Destroy(void) {
    Mix_HaltMusic();
    Mix_FreeMusic(m_music);

    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }

    SDL_DestroyTexture(d_arrowTexture);
    d_textures.clear();
    d_textures_draw_dest.clear();
    d_textures_draw_src.clear();
    return 0;
}

void MainMenu::Update(void) {
    if(d_buttonPressedDown and d_keyboardInput->IsKeyOn(SDLK_DOWN)) {
        d_buttonPressedDown = false;
        d_arrow++;
        if(d_arrow >= (int) corner) d_arrow = 0;
    }
    if(d_buttonPressedUp and d_keyboardInput->IsKeyOn(SDLK_UP)) {
        d_buttonPressedUp = false;
        d_arrow--;
        if(d_arrow < 0) d_arrow = (int) corner - 1;
    }
    if(d_buttonPressedEnter and d_keyboardInput->IsKeyOn(SDLK_RETURN)) {
        switch(d_arrow) {
            case 0:
                d_nextDisplay = new Loading(d_texture, d_renderer, d_windowWidth, d_windowHeight);
                d_leaveNext = true;
                break;
            case 1:
                d_leavePrevious = true;
                break;
            default:
                break;
        }
    }

    if(!(d_keyboardInput->IsKeyOn(SDLK_DOWN))) d_buttonPressedDown = true;
    if(!(d_keyboardInput->IsKeyOn(SDLK_UP))) d_buttonPressedUp = true;
    if(!(d_keyboardInput->IsKeyOn(SDLK_RETURN))) d_buttonPressedEnter = true;
}

void MainMenu::Draw(SDL_Renderer* renderer) const {
    for(int i = 0; i < (int) d_textures.size(); i++) {
        SDL_RenderCopy(renderer, d_textures[i], &d_textures_draw_src[i], &d_textures_draw_dest[i]);
    }

    SDL_Rect SrcR;
    SrcR.h = d_arrowHeight; SrcR.w = d_arrowWidth;
    SrcR.x = 0; SrcR.y = 0;

    SDL_Rect DestR;
    DestR.h = d_arrowHeight; DestR.w = d_arrowWidth;
    DestR.x = d_textures_draw_dest[d_arrow].x - d_arrowWidth - 50;
    DestR.y = d_textures_draw_dest[d_arrow].y;

    SDL_RenderCopy(renderer, d_arrowTexture, &SrcR, &DestR);
}


