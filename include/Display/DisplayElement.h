#ifndef DISPLAY_ELEMENT_H
#define DISPLAY_ELEMENT_H

#include "SDL.h"

class DisplayElement {
    public:
        DisplayElement(SDL_Texture* texture);

        virtual ~DisplayElement() = 0;
        DisplayElement(const DisplayElement& other) = delete;
        DisplayElement& operator=(const DisplayElement&) = delete;

        virtual void Update() = 0;
        virtual void Draw(SDL_Renderer* renderer) const = 0;

    protected:
        SDL_Texture* d_texture;

    private:
};

#endif // DISPLAY_ELEMENT_H


