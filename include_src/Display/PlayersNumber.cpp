#include "../../include/Display/PlayersNumber.h"
#include "../../include/System/TextRenderer.h"
#include "../../include/Constant/Resources.h"

using namespace std;

PlayersNumber::PlayersNumber(SDL_Renderer* renderer, int windowWidth, int windowHeight)
    : Display(),
      d_renderer(renderer),
      d_arrow(0),
      d_buttonPressedDown(false),
      d_buttonPressedUp(false),
      d_buttonPressedEnter(false),
      d_windowWidth(windowWidth),
      d_windowHeight(windowHeight) {

    string path_font = RESOURCE_BASE + RESOURCE_FONT;
    TextRenderer text_renderer(path_font, 60);

    SDL_Color color = {131, 238, 255, 0};
    SDL_Rect SrcR = {0, 0, 0, 0};
    SDL_Rect DestR = {0, 0, 0, 0};

    SDL_Texture* image;
    image = text_renderer.RenderText("CHOOSE GAME MODE:", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = windowWidth/2 -  SrcR.w/2;
    DestR.y = windowHeight/2 - SrcR.h/2 - SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("Single", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = windowWidth/2 -  SrcR.w/2 - 50;
    DestR.y += SrcR.h + 20;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("Local CO-OP", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.y += SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);

    d_arrowTexture = text_renderer.RenderText(">", color, renderer);
    SDL_QueryTexture(d_arrowTexture, NULL, NULL, &d_arrowWidth, &d_arrowHeight);
}

PlayersNumber::~PlayersNumber() {
    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }
    SDL_DestroyTexture(d_arrowTexture);
    d_textures.clear();
    d_textures_draw_dest.clear();
    d_textures_draw_src.clear();
}

void PlayersNumber::Init(void) {
    Enter();
}

void PlayersNumber::Enter(int mode) {
    d_leaveNext = false;
    d_leavePrevious = false;
    d_arrow = 1;
    d_buttonPressedDown = false;
    d_buttonPressedUp = false;
    d_buttonPressedEnter = false;
}

void PlayersNumber::Leave() { }

int PlayersNumber::Destroy() {
    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }
    SDL_DestroyTexture(d_arrowTexture);
    d_textures.clear();
    d_textures_draw_dest.clear();
    d_textures_draw_src.clear();
    return m_players_selected;
}

void PlayersNumber::Update() {
    if(d_buttonPressedDown and d_keyboardInput->IsKeyOn(SDLK_DOWN)) {
        d_buttonPressedDown = false;
        d_arrow++;
        if(d_arrow >= (int) d_textures.size()) d_arrow = 1;
    }
    if(d_buttonPressedUp and d_keyboardInput->IsKeyOn(SDLK_UP)) {
        d_buttonPressedUp = false;
        d_arrow--;
        if(d_arrow < 1) d_arrow = (int) d_textures.size() - 1;
    }
    if(d_buttonPressedEnter and d_keyboardInput->IsKeyOn(SDLK_RETURN)) {
        switch(d_arrow) {
            case 0:
            case 1:
                m_players_selected = 1;
                d_leavePrevious = true;
                break;
            case 2:
                m_players_selected = 2;
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

void PlayersNumber::Draw(SDL_Renderer* renderer) const {
    for(int i = 0; i < (int) d_textures.size(); i++) {
        SDL_RenderCopy(renderer, d_textures[i], &d_textures_draw_src[i], &d_textures_draw_dest[i]);
    }
    SDL_Rect SrcR;
    SrcR.h = d_arrowHeight;
    SrcR.w = d_arrowWidth;
    SrcR.x = 0;
    SrcR.y = 0;
    SDL_Rect DestR;
    DestR.h = d_arrowHeight;
    DestR.w = d_arrowWidth;
    DestR.x = d_textures_draw_dest[d_arrow].x - d_arrowWidth - 50;
    DestR.y = d_textures_draw_dest[d_arrow].y;
    SDL_RenderCopy(renderer, d_arrowTexture, &SrcR, &DestR);
}

