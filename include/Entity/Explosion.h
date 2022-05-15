#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SDL.h>
#include "../System/UltiTimer.h"

class Explosion {
    public:
        Explosion(int duration, int x_center, int y_center, double intensity, int tile_size, SDL_Texture* texture);
        void Update();
        bool IsExploding() const;
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        UTimer m_timer;
        int m_duration, m_phase_number;
        bool m_exploding;
        int m_x_center, m_y_center, m_tile_size;
        double m_intensity;
        SDL_Texture* m_texture;
        inline int min2(int a, int b) {
            return (a*(a < b) + b*(a >= b));
        }

};

#endif // EXPLOSION_H

