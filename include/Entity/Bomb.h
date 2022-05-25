#ifndef BOMB_H
#define BOMB_H

#include <SDL.h>
#include "../System/UltiTimer.h"

class Bomb {
    public:
        Bomb(int fuse_duration, SDL_Texture* texture, int x, int y, int bomb_size, int player_id, double intensity = 1.0, int damage = 25);
        int GetX() const {
            return m_x;
        }
        int GetY() const {
            return m_y;
        }
        int GetBombSize () const {
            return m_draw_size;
        }
        double GetIntensity () const {
            return m_intensity;
        }
        int GetDamage() const {
            return m_damage;
        }
        int GetPlayerId() const {
            return m_player_id;
        }
        void Update();
        bool Explode() const;
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        UTimer m_timer;
        int m_fuse_duration, m_x, m_y, m_draw_size, m_damage, m_phase_number;
        int m_player_id;
        SDL_Texture* m_texture;
        bool m_explode;
        double m_intensity;
};

#endif // BOMB_H

