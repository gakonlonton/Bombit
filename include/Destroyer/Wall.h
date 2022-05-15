#ifndef WALL_H
#define WALL_H

#include "../Manager/MapManager.h"

class WallDestroyer {
    public:
        WallDestroyer(Map* level, int start_x, int start_y, int tile_size, double intensity, int damage);

    protected:
        void Spread(int row, int col, int direction_row, int direction_col) const;
        void Destroy(int row, int col) const;
        double DistanceToCenter(int row, int col) const;
        void CheckAndCall(int new_row, int new_col, int direction_row, int direction_col) const;

    private:
        Map* m_level;
        int m_start_x, m_start_y, m_tile_size, m_damage;
        double m_intensity;

};

#endif // WALL_H

