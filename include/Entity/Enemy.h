#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include "../System/UltiTimer.h"
#include "Player.h"

class Enemy {
    public:
        Enemy(SDL_Texture* tex, int tile_size, int val_x = 1, int val_y = 1);

        virtual ~Enemy();
        Enemy(const Enemy& other) = delete;
        Enemy& operator=(const Enemy&) = delete;

        int GetX() const;
        int GetY() const;
        int GetSizeW() const;
        int GetSizeH() const;
        int GetStatus() const;
        int GetDirection() const;
        int GetHealth() const;

        void SetX(int val);
        void SetY(int val);
        void SetStatus(int s);
        void SetDirection(int d);
        void SetHealth(int h);

        void EnemyMove(Relay *relay);
        virtual void Draw(SDL_Renderer* renderer) = 0;
        virtual void Update(Relay *relay);
        bool Touch(int player_x, int player_y);

    protected:
        enum Direction {
              LEFT = 0,
              RIGHT = 1,
              UP = 2,
              DOWN = 3
        };
        Direction m_direction;
        int m_walk_len = 0;
        UTimer m_timer;
        int m_speed, m_rotation_const, m_status = 0, m_health = 100, m_x, m_y;
        int m_move_speed = 4, m_enemy_size_w, m_enemy_size_h, m_tile_size;
        SDL_Texture* m_tex;
    private:
};

#endif // ENEMY_H

