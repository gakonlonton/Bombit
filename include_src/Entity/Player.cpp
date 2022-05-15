#include "../../include/Entity/Player.h"
#include "../../include/Manager/MapManager.h"
#include "../../include/Manager/BombManager.h"
#include "../../include/Constant/PlayerTexture.h"
#include "../../include/Manager/PickupManager.h"
#include "../../include/Entity/Pickup.h"

#include <iostream>

const double MAX_BOMB_INTENSITY = 4;
const double MIN_BOMB_INTENSITY = 2.5;
const int MAX_LIVES = 5;
const int MAX_SPEED = 20;
const int MIN_SPEED = 200;
const int MAX_BOMBS = 5;
const int MIN_BOMBS = 1;
const int MAX_BOMB_DAMAGE = 100;
const int MIN_BOMB_DAMAGE = 25;

Player::Player(SDL_Texture* tex, int tile_size, Relay *relay, int val_x, int val_y)
      : m_keyboard_input(KeyboardInput::Instance()) {

    this -> m_x = val_x*tile_size;
    this -> m_y = val_y*tile_size;
    this -> m_input_x = m_x;
    this -> m_input_y = m_y;
    this -> m_tex = tex;
    this -> m_direction = DOWN;
    this -> m_status = 0;
    this -> m_tile_size = tile_size;

    m_timer.ResetTimer();
    m_player_size_w = TEXTURE_PLAYER_SIZE_W*tile_size/32;
    m_player_size_h = TEXTURE_PLAYER_SIZE_H*tile_size/32;
    m_move_speed = m_move_speed*m_tile_size/32;
    m_relay = relay;
}

bool Player::Touch(int pick_up_x, int pick_up_y) {
    if(pick_up_x >= m_x and pick_up_y >= m_y and
       pick_up_x <= m_x + m_player_size_w and pick_up_y <= m_y + m_player_size_h) {
        return true;
    }
    return false;
}

void Player::Update(void) {
    /// Pick up
    for(PickUpManager::Iterator it(m_relay->GetPickUpManager()); !it.Finished(); ++it) {
        PickUp& pick_up = it.GetPickUp();
        int pick_up_x = pick_up.GetX(), pick_up_y = pick_up.GetY();

        bool picked_up = false;
        if(Touch(pick_up_x, pick_up_y)) {
            picked_up = true;
        }

        if(picked_up) {
            switch(pick_up.GetType()) {
                case PickUp::EXIT:
                    if(!pick_up.IsUsed()) {
                        m_level_completed = true;
                        m_x = 0;
                        m_y = 0;
                    }
                    break;
                case PickUp::SPEED:
                    if(!pick_up.IsUsed()) {
                        if(m_speed > MAX_SPEED) {
                            m_speed -= pick_up.GetValue();
                            pick_up.Use();
                        }
                        else m_speed = MAX_SPEED;
                    }
                    break;
                case PickUp::BOMB:
                    if(!pick_up.IsUsed()) {
                        if(m_bomb_num < MAX_BOMBS) {
                            m_bomb_num += pick_up.GetValue();
                            pick_up.Use();
                        }
                        else m_bomb_num = MAX_BOMBS;
                    }
                    break;
                case PickUp::DAMAGE:
                    if(!pick_up.IsUsed()) {
                        bool isIncrease = false;
                        if(m_bomb_damage < MAX_BOMB_DAMAGE) {
                            m_bomb_damage += pick_up.GetValue();
                            pick_up.Use();
                            isIncrease = true;
                        }
                        else m_bomb_damage = MAX_BOMB_DAMAGE;
                        if(isIncrease and m_bomb_intensity < MAX_BOMB_INTENSITY) {
                            m_bomb_intensity += pick_up.GetValue()/100.0;
                        }
                        else m_bomb_intensity = MAX_BOMB_INTENSITY;
                    }
                    break;
                case PickUp::LIFE:
                    if(!pick_up.IsUsed()) {
                        if(m_lives < MAX_LIVES) {
                            m_lives += pick_up.GetValue();
                            pick_up.Use();
                        }
                        else m_lives = MAX_LIVES;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    /// Place bomb
    if(m_keyboard_input->IsKeyOn(m_bomb_button)) {
        m_bomb_ready = true;
    }
    else {
        if(!m_keyboard_input->IsKeyOn(m_bomb_button) and m_bomb_ready) {
             this->PlaceBomb();
             m_bomb_ready = false;
        }
    }

    if(m_timer.GetTimeElapsed() > m_speed) {
        /// Key Input
        if(m_keyboard_input->IsKeyOn(m_up)) {
            this -> PlayerMove(0, -1);
        }
        else if(m_keyboard_input->IsKeyOn(m_down)) {
            this -> PlayerMove(0, 1);
        }
        else if(m_keyboard_input->IsKeyOn(m_left)) {
            this -> PlayerMove(-1, 0);
        }
        else if(m_keyboard_input->IsKeyOn(m_right)) {
            this -> PlayerMove(1, 0);
        }
        else {
            this -> SetStatus(0);
        }
    }

    if(m_timer.GetTimeElapsed() > m_speed) {
        m_timer.DecreaseTimer(m_speed);
    }
}

void Player::PlaceBomb(void) {
    if(m_bomb_temp_num < m_bomb_num) {
		m_relay->GetBombManager()->MakeBomb(5000, m_x + m_player_size_w/2, m_y + m_player_size_h/2, m_bomb_intensity, m_bomb_damage);
        m_bomb_temp_num++;
    }
}

void Player::DecreaseTempBombNumber(void) {
    m_bomb_temp_num--;
}

void Player::Draw(SDL_Renderer *renderer) {
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.y = TEXTURE_PLAYER_Y;
    SrcR.w = TEXTURE_PLAYER_SOURCE_W;
    SrcR.h = TEXTURE_PLAYER_SOURCE_H;
    int source_texture_x = TEXTURE_PLAYER_MAIN_SOURCE_OFFSET;

    switch(m_direction) {
        case UP:
            if(m_status % m_rotation_const == 0) SrcR.x = source_texture_x + 3*TEXTURE_PLAYER_TEXTURE_OFFSET;
            if(m_status % m_rotation_const == 1) SrcR.x = source_texture_x + 4*TEXTURE_PLAYER_TEXTURE_OFFSET;
            if(m_status % m_rotation_const == 2) SrcR.x = source_texture_x + 5*TEXTURE_PLAYER_TEXTURE_OFFSET;
            break;
        case DOWN:
            if(m_status % m_rotation_const == 0) SrcR.x = source_texture_x;
            if(m_status % m_rotation_const == 1) SrcR.x = source_texture_x + TEXTURE_PLAYER_TEXTURE_OFFSET;
            if(m_status % m_rotation_const == 2) SrcR.x = source_texture_x + 2*TEXTURE_PLAYER_TEXTURE_OFFSET;
            break;
        case LEFT:
            if(m_status % m_rotation_const == 0) SrcR.x = source_texture_x + 6*TEXTURE_PLAYER_TEXTURE_OFFSET;
            if(m_status % m_rotation_const == 1) SrcR.x = source_texture_x + 7*TEXTURE_PLAYER_TEXTURE_OFFSET;
            if(m_status % m_rotation_const == 2) SrcR.x = source_texture_x + 8*TEXTURE_PLAYER_TEXTURE_OFFSET;
            break;
        case RIGHT:
            if(m_status % m_rotation_const == 0) SrcR.x = source_texture_x + 9*TEXTURE_PLAYER_TEXTURE_OFFSET;
            if(m_status % m_rotation_const == 1) SrcR.x = source_texture_x + 10*TEXTURE_PLAYER_TEXTURE_OFFSET;
            if(m_status % m_rotation_const == 2) SrcR.x = source_texture_x + 11*TEXTURE_PLAYER_TEXTURE_OFFSET;
            break;
    }

    DestR.x = m_x;
    DestR.y = m_y;
    DestR.w = m_player_size_w;
    DestR.h = m_player_size_h;

    SDL_RenderCopy(renderer, m_tex, &SrcR, &DestR);
}

void Player::PlayerMove(int x, int y) {
    int field_size = m_tile_size;
    if(x == 1) {
        m_direction = RIGHT;
        if(m_relay->GetMap()->Walkable(m_y/field_size, (m_x + m_player_size_w + m_move_speed)/field_size) and m_relay->GetMap()->Walkable((m_y + m_player_size_h)/field_size, (m_x + m_player_size_w + m_move_speed)/field_size)) {
            m_x = m_x + m_move_speed;
        }
    }
    else if(x == -1) {
        m_direction = LEFT;
        if(m_relay->GetMap()->Walkable(m_y/field_size, (m_x - m_move_speed)/field_size) and m_relay->GetMap()->Walkable((m_y + m_player_size_h)/field_size, (m_x - m_move_speed)/field_size)) {
            m_x = m_x - m_move_speed;
        }
    }
    else if(y == 1) {
        m_direction = DOWN;
        if(m_relay->GetMap()->Walkable((m_y + m_player_size_h + m_move_speed)/field_size, m_x/field_size) and m_relay->GetMap()->Walkable((m_y + m_player_size_h + m_move_speed)/field_size, (m_x + m_player_size_w)/field_size)) {
            m_y = m_y + m_move_speed;
        }
    }
    else if(y == -1) {
        m_direction = UP;
        if(m_relay->GetMap()->Walkable( (m_y - m_move_speed)/field_size, m_x/field_size) and m_relay->GetMap()->Walkable((m_y - m_move_speed)/field_size, (m_x+m_player_size_w)/field_size)) {
            m_y = m_y - m_move_speed;
        }
    }
    m_status++;
    if(m_status >= m_rotation_const) m_status = 0;
}

int Player::GetX() const {
    return m_x;
}

void Player::SetX(int val) {
    if(val != -1) m_x = val;
    else m_x = m_input_x;
}

int Player::GetY() const {
    return m_y;
}

void Player::SetY(int val) {
    if(val != -1) m_y = val;
    else m_y = m_input_y;
}

int Player::GetSizeW() const {
    return m_player_size_w;
}

int Player::GetSizeH() const {
    return m_player_size_h;
}

int Player::GetStatus() const {
    return m_status;
}

void Player::SetStatus(int s) {
    m_status = s;
}

int Player::GetDirection() const {
    return m_direction;
}

void Player::SetDirection(int d) {
    switch(d) {
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

int Player::GetHealth() const {
    return m_health;
}

void Player::SetHealth(int h) {
    m_health = h;
}

void Player::SetKeycodes(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right, SDL_Keycode bomb_button) {
    m_up = up;
    m_down = down;
    m_left = left;
    m_right = right;
    m_bomb_button = bomb_button;
}

int Player::GetAlive() const {
    return m_alive;
}

void Player::SetAlive(int a) {
    m_alive = a;
}

int Player::GetLives() const {
    return m_lives;
}

void Player::SetLives(int l) {
    m_lives = l;
}

bool Player::IsLevelCompleted() const {
    return m_level_completed;
}

bool Player::IsAlive() const {
    if(m_alive == 1) return true;
    else return false;
}

