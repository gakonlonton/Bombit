#include <bits/stdc++.h>
#include <SDL.h>
#include "SDL_image.h"
#include "../../include/Display/DisplayUtilities.h"
#include "../../include/Constant/Resources.h"
#include "../../include/System/TextRenderer.h"
#include "../../include/Display/MainMenu.h"

using namespace std;

WelcomeDisplay::WelcomeDisplay(SDL_Texture* texture, SDL_Renderer* renderer,
                               int windowWidth, int windowHeight)
    : Display(),
      d_texture(texture), d_renderer(renderer),
      d_pressedNext(false), d_pressedPrevious(false),
      d_windowWidth(windowWidth), d_windowHeight(windowHeight) {



    string path_font = RESOURCE_BASE + RESOURCE_FONT;
    TextRenderer text_renderer(path_font, 54);
    SDL_Color color = {255, 255, 255, 0};
    SDL_Rect SrcR = {0, 0, 0, 0};
    SDL_Rect DestR = {0, 0, 0, 0};

    SDL_Texture* image;

    image = text_renderer.RenderText("Welcome to Phi Hung's BombIT", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = windowWidth/2 -  SrcR.w/2;
    DestR.y = windowHeight/2 - SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);

    image = text_renderer.RenderText("Press ENTER to start", color, renderer);
    SDL_QueryTexture(image, NULL, NULL, &(SrcR.w), &(SrcR.h));
    DestR.x = DestR.x + (DestR.w - SrcR.w)/2;
    DestR.y += SrcR.h;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;
    d_textures.push_back(image);
    d_textures_draw_src.push_back(SrcR);
    d_textures_draw_dest.push_back(DestR);
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
    if(d_pressedNext && d_keyboardInput->IsKeyOn(SDLK_RETURN)) {
        d_pressedNext = false;
        d_nextDisplay = new MainMenu(d_texture, d_renderer, d_windowWidth, d_windowHeight);
        d_leaveNext = true;
    }
    if(d_pressedPrevious && d_keyboardInput->IsKeyOn(SDLK_ESCAPE)) {
        d_pressedPrevious = false;
        d_leavePrevious = true;
    }

    if(!(d_keyboardInput->IsKeyOn(SDLK_RETURN))) d_pressedNext = true;
    if(!(d_keyboardInput->IsKeyOn(SDLK_ESCAPE))) d_pressedPrevious = true;
}

void WelcomeDisplay::Draw(SDL_Renderer* renderer) const {
    for(unsigned int i = 0; i < (int) d_textures.size(); i++) {
        SDL_RenderCopy(renderer, d_textures[i], &d_textures_draw_src[i], &d_textures_draw_dest[i]);
    }
}

SDL_Texture* load_image(string path, SDL_Renderer* renderer) {
    SDL_Texture* new_texture = nullptr;
    SDL_Surface* loadedSF = IMG_Load(path.c_str());
    if(loadedSF == nullptr) {
        cout << "Unable to load image " << path << " SDL_image: Error: "
                 << IMG_GetError() << "\n";
        return false;
    }
    else {
        new_texture = SDL_CreateTextureFromSurface(renderer, loadedSF);
        SDL_FreeSurface(loadedSF);
        if(new_texture == nullptr) {
            cout << "Unable to create texture from " << path << " SDL: Error: "
                 << SDL_GetError() << "\n";
        }
    }
    return new_texture;
}
