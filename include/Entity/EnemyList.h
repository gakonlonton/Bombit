#ifndef ENEMY_LIST_H
#define ENEMY_LIST_H


#include <SDL.h>
#include <bits/stdc++.h>
#include "../System/Relay.h"
#include "../System/UltiTimer.h"
#include "Player.h"
#include "Enemy.h"

class EnemyOne : public Enemy {
    public:
        EnemyOne(SDL_Texture* tex, int tile_size, int val_x = 1, int val_y = 1);
        void Draw(SDL_Renderer* renderer);
    protected:

    private:
};

class EnemyTwo : public Enemy {
    public:
       public:
        EnemyTwo(SDL_Texture* tex, int tile_size, int val_x = 1, int val_y = 1);
        void Draw(SDL_Renderer* renderer);
    protected:

    private:
};

class EnemyThree : public Enemy {
    public:
        EnemyThree(SDL_Texture* tex, int tile_size, int val_x = 1, int val_y = 1);
        void Draw(SDL_Renderer* renderer);
        void Update(Relay* relay);
        void ChasePlayer(Player* player, Relay* relay);
        bool DirectionCheck(Direction d, Relay* relay);
    protected:

    private:
        bool m_chase = false;
};

#endif // ENEMY_LIST_H

