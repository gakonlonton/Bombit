#ifndef PICKUP_H
#define PICKUP_H

#include <SDL.h>

class PickUp {
    public:
        enum PickUpType {
            EXIT, SPEED, BOMB, DAMAGE, LIFE
        };

        PickUp(SDL_Texture* texture, PickUpType type, int value, int x, int y, int draw_size);

        PickUpType GetType() const {
            return m_type;
        }
        int GetValue() const {
            return m_value;
        }
        int GetX() const {
            return m_x;
        }
        int GetY() const {
            return m_y;
        }
        int GetSize() const {
            return m_draw_size;
        }
        bool IsUsed() const;
        void Use();
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        SDL_Texture* m_texture;
        PickUpType m_type;
        int m_value, m_x, m_y, m_draw_size;
        bool m_used;

};

#endif // PICKUP_H


