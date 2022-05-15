#include "../../include/Display/PauseDisplay.h"
#include "../../include/System/TextRenderer.h"
#include "../../include/Constant/Resources.h"

using namespace std;

PauseDisplay::PauseDisplay(SDL_Renderer* renderer,
                           int windowWidth, int windowHeight,
                           Display* previousDisplay)
    : Display(),
      d_renderer(renderer),
      d_arrow(0),
      d_windowWidth(windowWidth),
      d_windowHeight(windowHeight),
      d_quit(false),
      d_previousDisplay(previousDisplay) {

    string path_font = RESOURCE_BASE + RESOURCE_FONT;
    TextRenderer text_renderer(path_font, 64);

    SDL_Color color = {255, 255, 255, 0};
    SDL_Rect SrcR = {0, 0, 0, 0};
    SDL_Rect DestR = {0, 0, 0, 0};
    SDL_Texture* image;

    image = text_renderer.RenderText("RESUME", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = windowWidth/2 -  SrcR.w/2;
    DestR.y = windowHeight/2 - SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("QUIT", color, renderer);
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

PauseDisplay::~PauseDisplay(void) {
    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }

    SDL_DestroyTexture(d_arrowTexture);
    d_textures.clear();
    d_textures_draw_dest.clear();
    d_textures_draw_src.clear();
}

void PauseDisplay::Init(void) {
    Enter(0);
}

void PauseDisplay::Enter(int mode) {
    d_leaveNext = false;
    d_leavePrevious = false;
    d_buttonPressedDown = false;
    d_buttonPressedUp = false;
    d_buttonPressedEnter = false;
}

void PauseDisplay::Leave() {}

int PauseDisplay::Destroy() {
    for(auto i = d_textures.begin(); i != d_textures.end(); i++) {
        SDL_DestroyTexture(*i);
    }

    SDL_DestroyTexture(d_arrowTexture);
    d_textures.clear();
    d_textures_draw_dest.clear();
    d_textures_draw_src.clear();

    if(d_quit) return 0;
    return 1;
}

void PauseDisplay::Update() {
    if(d_buttonPressedDown && d_keyboardInput->IsKeyOn(SDLK_DOWN)) {
        d_buttonPressedDown = false;
        d_arrow++;
        if(d_arrow >= (int) d_textures.size()) d_arrow = 0;
    }
    if(d_buttonPressedUp && d_keyboardInput->IsKeyOn(SDLK_UP)) {
        d_buttonPressedUp = false;
        d_arrow--;
        if(d_arrow < 0) d_arrow = (int) d_textures.size() - 1;
    }
    if (d_buttonPressedEnter && d_keyboardInput->IsKeyOn(SDLK_RETURN)) {
        switch(d_arrow) {
            case 0:
                d_quit = false;
                d_leavePrevious = true;
                break;
            case 1:
                d_quit = true;
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

void PauseDisplay::Draw(SDL_Renderer* renderer) const {
    if(d_previousDisplay != nullptr) d_previousDisplay->Draw(renderer);
    for(unsigned int i = 0; i < (int) d_textures.size(); i++) {
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

