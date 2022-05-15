#include <bits/stdc++.h>
#include "../../include/Entity/EnemyList.h"
#include "../../include/Manager/MapManager.h"
#include "../../include/Manager/PlayerManager.h"
#include "../../include/Constant/EnemyTexture.h"

using namespace std;

/// Enemy One

EnemyOne::EnemyOne(SDL_Texture* tex, int tile_size, int val_x, int val_y) : Enemy(tex, tile_size, val_x, val_y) {
    m_speed = 100;
    m_move_speed = m_move_speed *m_tile_size/32;
    m_rotation_const = TEXTURE_ENEMY_ONE_COUNT;
    m_enemy_size_w = TEXTURE_ENEMY_ONE_SIZE_W*tile_size/32;
    m_enemy_size_h = TEXTURE_ENEMY_ONE_SIZE_H*tile_size/32;
}

void EnemyOne::Draw(SDL_Renderer *renderer) {
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = TEXTURE_ENEMY_ONE_X + (m_status % m_rotation_const) * TEXTURE_ENEMY_ONE_TEXTURE_OFFSET;
    SrcR.y = TEXTURE_ENEMY_ONE_Y;
    SrcR.w = TEXTURE_ENEMY_ONE_SOURCE_W;
    SrcR.h = TEXTURE_ENEMY_ONE_SOURCE_H;

    DestR.x = m_x;
    DestR.y = m_y;
    DestR.w = m_enemy_size_w;
    DestR.h = m_enemy_size_h;

    SDL_RenderCopy(renderer, m_tex, &SrcR, &DestR);
}

/// Enemy Two

EnemyTwo::EnemyTwo(SDL_Texture* tex, int tile_size, int val_x, int val_y) : Enemy(tex, tile_size, val_x, val_y) {
    m_speed = 74;
    m_move_speed = m_move_speed * m_tile_size/32;
    m_rotation_const = TEXTURE_ENEMY_TWO_COUNT;
    m_enemy_size_w = TEXTURE_ENEMY_TWO_SIZE_W * tile_size/32;
    m_enemy_size_h = TEXTURE_ENEMY_TWO_SIZE_H * tile_size/32;
}

void EnemyTwo::Draw(SDL_Renderer *renderer) {
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = TEXTURE_ENEMY_TWO_X + (m_status % m_rotation_const) * TEXTURE_ENEMY_TWO_TEXTURE_OFFSET;
    SrcR.y = TEXTURE_ENEMY_TWO_Y;
    SrcR.w = TEXTURE_ENEMY_TWO_SOURCE_W;
    SrcR.h = TEXTURE_ENEMY_TWO_SOURCE_H;

    DestR.x = m_x;
    DestR.y = m_y;
    DestR.w = m_enemy_size_w;
    DestR.h = m_enemy_size_h;

    SDL_RenderCopy(renderer, m_tex, &SrcR, &DestR);
}

/// Enemy Three

EnemyThree::EnemyThree(SDL_Texture* tex, int tile_size, int val_x, int val_y) : Enemy(tex, tile_size, val_x, val_y) {
    m_speed = 100;
    m_move_speed = m_move_speed * m_tile_size/32;
    m_rotation_const = TEXTURE_ENEMY_THREE_COUNT;
    m_enemy_size_w = TEXTURE_ENEMY_THREE_SIZE_W * tile_size/32;
    m_enemy_size_h = TEXTURE_ENEMY_THREE_SIZE_H * tile_size/32;
}

void EnemyThree::Draw(SDL_Renderer* renderer) {
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.x = TEXTURE_ENEMY_THREE_X + (m_status % m_rotation_const) * TEXTURE_ENEMY_THREE_TEXTURE_OFFSET;
    SrcR.y = TEXTURE_ENEMY_THREE_Y;
    SrcR.w = TEXTURE_ENEMY_THREE_SOURCE_W;
    SrcR.h = TEXTURE_ENEMY_THREE_SOURCE_H;

    DestR.x = m_x;
    DestR.y = m_y;
    DestR.w = m_enemy_size_w;
    DestR.h = m_enemy_size_h;

    SDL_RenderCopy(renderer, m_tex, &SrcR, &DestR);
}

void EnemyThree::Update(Relay *relay) {
    int player_min = -1;
    Player* p = nullptr;
    int x, y;
    for(PlayerManager::Iterator it(relay->GetPlayerManager()); !it.Finished(); ++it) {
        Player& player = it.GetPlayer();
        int player_x = player.GetX();
        int player_y = player.GetY();
        int player_w = player.GetSizeW();
        int player_h = player.GetSizeH();
        player_x = player_x + m_tile_size/6;
        player_y = player_y + m_tile_size/6;
        player_w = player_w - m_tile_size/3;
        player_h = player_h - m_tile_size/4;
        if(Touch(player_x, player_y)) {
            player.SetHealth(0);
        }
        else if(Touch(player_x + player_w, player_y)) {
            player.SetHealth(0);
        }
        else if(Touch(player_x, player_y + player_h)) {
            player.SetHealth(0);
        }
        else if(Touch(player_x + player_w, player_y + player_h)) {
            player.SetHealth(0);
        }
        x = m_x - player.GetX();
        y = m_y - player.GetY();
        if(player_min > sqrt(x*x + y*y)) {
            player_min = sqrt(x*x + y*y);
            p = &player;
        }
    }
    if(player_min <= 2*m_tile_size) m_chase = true;
    else m_chase = false;

    if(m_chase) {
        ChasePlayer(p, relay);
    }
    else {
        int type = 0;
        if(m_walk_len <= 0) {

            m_walk_len = rand()%5 + 10;
            type = rand()%4;
            switch(type) {
                case 0:
                    m_direction = LEFT;
                    break;
                case 1:
                    m_direction = RIGHT;
                    break;
                case 2:
                    m_direction = UP;
                    break;
                case 3:
                    m_direction = DOWN;
                    break;
                default:
                    m_direction = DOWN;
            }
        }
    }
    if(m_timer.GetTimeElapsed() > m_speed) {
        m_walk_len--;
        this->EnemyMove(relay);
        m_timer.ResetTimer();
    }
}

void EnemyThree::ChasePlayer(Player * player, Relay *relay) {
    int i = 1, j = 1;
    Direction direction1 = LEFT, direction2;

    if(m_x > player->GetX()) {
        if(DirectionCheck(LEFT, relay)) direction1 = LEFT;
        else i = 0;
    }
    else {
        if(DirectionCheck(RIGHT, relay) ) direction1 = RIGHT;
        else i = 0;
    }
    if(m_y > player->GetY()) {
        if(DirectionCheck(UP, relay)) direction2 = UP;
        else j = 0;
    }
    else {
        if(DirectionCheck(DOWN, relay)) direction2 = DOWN;
        else j = 0;
    }
    if((abs((int) m_x - (int) player->GetX()) > abs((int) m_y - (int) player->GetY())) and i != 0) m_direction = direction1;
    else {
        if(j != 0) m_direction = direction2;
        else m_direction = direction1;
    }
}

bool EnemyThree::DirectionCheck(Direction d, Relay *relay) {
    int field_size = m_tile_size;
    if(d == RIGHT) {
        if(relay->GetMap()->Walkable(m_y/field_size, (m_x + m_enemy_size_w + m_move_speed)/field_size)
           and relay->GetMap()->Walkable((m_y + m_enemy_size_h)/field_size, (m_x + m_enemy_size_w + m_move_speed)/field_size)) {
            return true;
        }
    }
    else if (d == LEFT) {
        if(relay->GetMap()->Walkable(m_y/field_size, (m_x - m_move_speed)/field_size)
           and relay->GetMap()->Walkable((m_y + m_enemy_size_h)/field_size, (m_x - m_move_speed)/field_size)) {
            return true;
        }
    }
    else if(d == DOWN) {
        if(relay->GetMap()->Walkable((m_y + m_enemy_size_h + m_move_speed)/field_size, m_x/field_size)
           and relay->GetMap()->Walkable((m_y + m_enemy_size_h + m_move_speed)/field_size, (m_x + m_enemy_size_w)/field_size)) {
            return true;
        }
    }
    else if(d == UP) {
        if(relay->GetMap()->Walkable((m_y - m_move_speed)/field_size, m_x/field_size)
           and relay->GetMap()->Walkable((m_y - m_move_speed)/field_size, (m_x + m_enemy_size_w)/field_size)) {
            return true;
        }
    }
    return false;
}




