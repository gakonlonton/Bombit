#ifndef DESTROYER_H
#define DESTROYER_H

#include "../Entity/Enemy.h"
#include "../Entity/Player.h"

class Destroyer {
    public:
        static void DestroyEnemy(Enemy* enemy, int start_x, int start_y, int tile_size, double intensity);
        static void DestroyPlayer(Player* player, int start_x, int start_y, int tile_size, double intensity);

    protected:
        static int Square(int x) {
            return x*x;
        }

    private:
        Destroyer();
};

#endif // DESTROYER_H

