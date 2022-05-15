#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include <SDL.h>

class MapObject {
    public:
        enum Tile {
              EMPTY = 0,
              DESTRUCTIBLE_WALL = 1,
              INDESTRUCTIBLE_WALL = 2
        };
        MapObject(Tile id, SDL_Texture *texture, int kind = 0);

        virtual ~MapObject() { };
        MapObject(const MapObject& other) = delete;
        MapObject& operator=(const MapObject&) = delete;

        Tile GetId() const {
            return m_id;
        }
        virtual void Draw(SDL_Renderer* renderer, const SDL_Rect *DestR);

    protected:
        Tile m_id;
        SDL_Texture* m_texture;
        int m_kind;

    private:
};

#endif // MAP_OBJECT_H


