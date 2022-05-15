#include "../../include/Destroyer/Wall.h"
#include <cmath>
using namespace std;

WallDestroyer::WallDestroyer(Map* level, int start_x, int start_y, int tile_size, double intensity, int damage)
    :   m_level(level), m_start_x(start_x), m_start_y(start_y), m_tile_size(tile_size), m_intensity(intensity/2), m_damage(damage) {
    int i = m_start_y/tile_size;
    int j = m_start_x/tile_size;
    CheckAndCall(i-1, j, -1, 0);       //UP
    CheckAndCall(i+1, j, 1, 0);        //DOWN
    CheckAndCall(i, j-1, 0, -1);       //LEFT
    CheckAndCall(i, j+1, 0, 1);        //RIGHT
    CheckAndCall(i-1, j-1, -1, -1);    //UP LEFT
    CheckAndCall(i-1, j+1, -1, 1);     //UP RIGHT
    CheckAndCall(i+1, j-1, 1, -1);     //DOWN LEFT
    CheckAndCall(i+1, j+1, 1, 1);      //DOWN RIGHT
}

void WallDestroyer::Spread(int row, int col, int direction_row, int direction_col) const {
    if(direction_row != 0) CheckAndCall(row + direction_row, col, direction_row, direction_col);
    if(direction_col != 0) CheckAndCall(row, col + direction_col, direction_row, direction_col);
    if(direction_row != 0 and direction_col != 0) CheckAndCall(row + direction_row, col + direction_col, direction_row, direction_col);
}

void WallDestroyer::Destroy(int row, int col) const {
    double distance = DistanceToCenter(row, col);
    if(distance < m_intensity*m_tile_size) {
        m_level->DestroyWall(row, col, m_damage);
    }
}

double WallDestroyer::DistanceToCenter(int row, int col) const {
    int wall_center_x = col*m_tile_size + m_tile_size/2;
    int wall_center_y = row*m_tile_size + m_tile_size/2;
    int X = m_start_x - wall_center_x;
    int Y = m_start_y - wall_center_y;
    return sqrt(X*X + Y*Y);
}

void WallDestroyer::CheckAndCall(int new_row, int new_col, int direction_row, int direction_col) const {
    if(DistanceToCenter(new_row, new_col) < m_intensity*m_tile_size) {
        MapObject::Tile tile = m_level->GetTileType(new_row, new_col);
        if(tile == MapObject::EMPTY) Spread(new_row, new_col, direction_row, direction_col);
        else if(tile == MapObject::DESTRUCTIBLE_WALL) Destroy(new_row, new_col);
    }
}

