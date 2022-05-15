#include "../../include/Destroyer/Destroyer.h"
#include <cmath>

using namespace std;

Destroyer::Destroyer() {}

void Destroyer::DestroyEnemy(Enemy* enemy, int start_x, int start_y, int tile_size, double intensity) {
    int enemy_center_x = enemy->GetX() + enemy->GetSizeW()/2;
    int enemy_center_y = enemy->GetY() + enemy->GetSizeH()/2;
    double distance = sqrt(Square(start_x - enemy_center_x) + Square(start_y - enemy_center_y));
    if(distance < tile_size*intensity/2) enemy->SetHealth(0);
}

void Destroyer::DestroyPlayer(Player* player, int start_x, int start_y, int tile_size, double intensity) {
    int player_center_x = player->GetX() + player->GetSizeW()/2;
    int player_center_y = player->GetY() + player->GetSizeH()/2;
    double distance = sqrt(Square(start_x - player_center_x) + Square(start_y - player_center_y));
    if (distance < tile_size*intensity/2) player->SetHealth(0);
}

