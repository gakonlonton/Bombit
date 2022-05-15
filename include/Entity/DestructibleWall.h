#ifndef DESTRUCTIBLE_WALL_H
#define DESTRUCTIBLE_WALL_H


#include "MabObject.h"

class DestructibleWall : public MapObject {
    public:
        DestructibleWall(SDL_Texture *texture, int kind);

        virtual ~DestructibleWall() { };
        DestructibleWall(const DestructibleWall& other) = delete;
        DestructibleWall& operator=(const DestructibleWall&) = delete;

        bool IsDestroyed() const;
        void DecreaseIntegrity(int value);
        virtual void Draw(SDL_Renderer* renderer, const SDL_Rect *DestR);

    protected:

    private:
        int m_integrity;
        static const int S_MAX_INTEGRITY = 100;
        inline int min2(int a, int b) {
            return (a*(a < b) + b*(a >= b));
        }
};

#endif // DESTRUCTIBLE_WALL_H

