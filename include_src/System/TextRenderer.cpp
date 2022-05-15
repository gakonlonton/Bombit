#include "../../include/System/TextRenderer.h"

using namespace std;

TextRenderer::TextRenderer(const string &font_file, int font_size):t_font(nullptr) {
    t_font = TTF_OpenFont(font_file.c_str(), font_size);
}

TextRenderer::~TextRenderer(void) {
    TTF_CloseFont(t_font);
}

SDL_Texture* TextRenderer::RenderText(const string &message, SDL_Color color, SDL_Renderer *renderer) {
    if(t_font == nullptr) return nullptr;

	SDL_Surface *surf = TTF_RenderText_Blended(t_font, message.c_str(), color);
	if (surf == nullptr){
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
        return nullptr;
	}
	SDL_FreeSurface(surf);
	return texture;
}

