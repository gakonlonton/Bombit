#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "../System/Relay.h"
#include "../System/KeyboardInput.h"
#include "../System/UltiTimer.h"

class Player {
    public:
        Player(SDL_Texture* tex, int tile_size, Relay *relay, int player_id = 0, int val_x = 1, int val_y = 1);

        void SetX(int val);
        void SetY(int val);
        void SetStatus(int val);
        void SetAlive(int val);
        void SetLives(int val);
        void SetDirection(int val);
        void SetHealth(int val);
        int GetX() const;
        int GetY() const;
        int GetSizeW() const;
        int GetSizeH() const;
        int GetStatus() const;
        int GetAlive() const;
        int GetLives() const;
        int GetDirection() const;
        int GetHealth() const;
        int GetID() const;

        bool IsLevelCompleted() const;
        bool IsAlive() const;

        void SetKeycodes(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right, SDL_Keycode bomb_button);
        void PlayerMove(int x, int y);
        void Draw(SDL_Renderer* renderer);
        void PlaceBomb();
        void Update();
        void DecreaseTempBombNumber();
        bool Touch(int pick_up_x, int pick_up_y);

    protected:

    private:
        enum Direction {
              LEFT = 0,
              RIGHT = 1,
              UP = 2,
              DOWN = 3
        };

        Direction m_direction;
        bool m_bomb_ready = false;
        bool m_level_completed = false;
        int m_status;
        UTimer m_timer;
        int m_bomb_num = 4, m_bomb_temp_num = 0;
        double m_bomb_intensity = 2.5;
        int m_bomb_damage = 25;
        int m_input_x, m_input_y;
        int m_lives = 3;
        int m_player_id;
        int m_alive = 1;
        int m_health = 100;
        int m_speed = 100;
        int m_x, m_y;
        int m_move_speed = 4;
        int m_rotation_const = 3;
        int m_player_size_w, m_player_size_h;
        SDL_Texture* m_tex;
        int m_tile_size;
        Relay* m_relay;
        KeyboardInput* m_keyboard_input;
        SDL_Keycode m_bomb_button = SDLK_SPACE;
        SDL_Keycode m_left = SDLK_LEFT;
        SDL_Keycode m_right = SDLK_RIGHT;
        SDL_Keycode m_up = SDLK_UP;
        SDL_Keycode m_down = SDLK_DOWN;

};

#endif // PLAYER_H

