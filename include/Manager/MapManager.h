#ifndef MAP_H
#define MAP_H

#include <bits/stdc++.h>
#include <SDL.h>
#include "../Display/DisplayElement.h"
#include "../System/Relay.h"
#include "../Entity/MabObject.h"

using namespace std;

class Map : public DisplayElement {
    public:
        Map(string path_to_file, SDL_Texture* texture, int tile_size, Relay* relay);

        ~Map();
        Map(const Map& other) = delete;
        Map& operator=(const Map&) = delete;

        int GetHeight() const {
            return m_height;
        }
        int GetWidth() const {
            return m_width;
        }
        int GetTileSize() const {
            return m_tile_size;
        }
        bool Walkable(int i, int j) const;
        void Draw(SDL_Renderer* renderer) const;
        void DestroyWall(int i, int j, int damage);
        MapObject::Tile GetTileType(int i, int j) const;
        void Update() {}

    protected:
        void PlaceExit(int i, int j);
        void TryPlacePickUp(int i, int j);

    private:
        int m_height, m_width, m_wall_count;
        vector<vector<MapObject*>> m_layout;
        const int m_tile_size;
        Relay* m_relay;
};

#endif // MAP_H

