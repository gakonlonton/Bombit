#include <bits/stdc++.h>
#include "../../include/Manager/MapManager.h"
#include "../../include/Constant/MapObjectTexture.h"
#include "../../include/Constant/PickupConstant.h"
#include "../../include/Entity/Pickup.h"
#include "../../include/Manager/PickupManager.h"
#include "../../include/Entity/DestructibleWall.h"

using namespace std;

Map::Map(string path_to_file, SDL_Texture* texture, int tile_size, Relay* relay) : DisplayElement(texture),
      m_tile_size(tile_size), m_relay(relay), m_wall_count(0) {
    fstream fs;
    fs.open (path_to_file, fstream::in);
    if (!fs.is_open()) exit(0);
    fs >> m_height >> m_width;
    m_layout.resize(m_height);
    for(int i = 0; i < m_height; i++) {
        m_layout[i].resize(m_width);
    }

    srand(time(nullptr));
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            int type; fs >> type;
            switch(type) {
                case 0:
                    m_layout[i][j] = new MapObject(MapObject::EMPTY, d_texture, rand()%TEXTURE_MAP_EMPTY_COUNT);
                    break;
                case 1:
                    m_layout[i][j] = new DestructibleWall(d_texture, rand()%TEXTURE_MAP_DESTRUCTIBLE_COUNT);
                    m_wall_count++;
                    break;
                case 2:
                    m_layout[i][j] = new MapObject(MapObject::INDESTRUCTIBLE_WALL, d_texture, rand()%TEXTURE_MAP_INDESTRUCTIBLE_COUNT);
                    break;
                default:
                    m_layout[i][j] = new MapObject(MapObject::EMPTY, d_texture);
                    break;
            }
        }
    }
    fs.close();
    srand(time(NULL));
}

Map::~Map(void) {
    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            delete m_layout[i][j];
        }
    }
}

bool Map::Walkable(int i, int j) const {
    if(m_layout[i][j]->GetId() == MapObject::EMPTY) return true;
    else return false;
}

void Map::Draw(SDL_Renderer* renderer) const {
    SDL_Rect DestR;
    int tile_size = m_tile_size;
    DestR.x = DestR.y = 0;
    DestR.w = DestR.h = tile_size;

    for(int i = 0; i < m_height; i++) {
        for(int j = 0; j < m_width; j++) {
            DestR.y = tile_size*i;
            DestR.x = tile_size*j;
            m_layout[i][j]->Draw(renderer, &DestR);
        }
    }
}

void Map::DestroyWall(int i, int j, int damage) {
    if(m_layout[i][j]->GetId() == MapObject::DESTRUCTIBLE_WALL) {
        DestructibleWall* wall = (DestructibleWall*) m_layout[i][j];
        wall->DecreaseIntegrity(damage);
        if(wall->IsDestroyed()) {
            delete m_layout[i][j];
            m_layout[i][j] = new MapObject(MapObject::EMPTY, d_texture);
            m_wall_count--;
            if(m_wall_count == 0) PlaceExit(i,j);
            else TryPlacePickUp(i,j);
        }
    }
}

MapObject::Tile Map::GetTileType(int i, int j) const {
    return m_layout[i][j]->GetId();
}

void Map::PlaceExit(int i, int j) {
    int x = m_tile_size*j + m_tile_size/2;
    int y = m_tile_size*i + m_tile_size/2;
    m_relay->GetPickUpManager()->MakePickUp(PickUp::EXIT, x, y);
}

void Map::TryPlacePickUp(int i, int j) {
    int x = m_tile_size*j + m_tile_size/2;
    int y = m_tile_size*i + m_tile_size/2;
    int chance = rand()%100;
    int type = rand()%PICKUPS_NUM;
    switch(type)
    {
        case 0:
            if(chance < CHANCE_EXIT) m_relay->GetPickUpManager()->MakePickUp(PickUp::EXIT, x, y);
            break;
        case 1:
            if(chance < CHANCE_SPEED) m_relay->GetPickUpManager()->MakePickUp(PickUp::SPEED, x, y, VALUE_SPEED);
            break;
        case 2:
            if(chance < CHANCE_BOMB) m_relay->GetPickUpManager()->MakePickUp(PickUp::BOMB, x, y, VALUE_BOMB);
            break;
        case 3:
            if(chance < CHANCE_DAMAGE) m_relay->GetPickUpManager()->MakePickUp(PickUp::DAMAGE, x, y, VALUE_DAMAGE);
            break;
        case 4:
            if(chance < (int) CHANCE_LIFE) m_relay->GetPickUpManager()->MakePickUp(PickUp::LIFE, x, y, VALUE_LIFE);
            break;
        default:
            break;
    }

}

