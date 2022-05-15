#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class TextRenderer {
    public:
        TextRenderer(const string &font_file, int font_size);
        SDL_Texture* RenderText(const string &message, SDL_Color color, SDL_Renderer *renderer);
        ~TextRenderer();
        TextRenderer(const TextRenderer& other) = delete;
        TextRenderer& operator=(const TextRenderer&) = delete;

    protected:
    private:
        TTF_Font* t_font;
};

#endif // TEXT_RENDERER_H

