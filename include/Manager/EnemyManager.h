#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <list>
#include "../Display/DisplayElement.h"
#include "../System/Relay.h"
#include "../Entity/Enemy.h"

using namespace std;

class EnemyManager : public DisplayElement {
    public:
        EnemyManager(string path_to_file,SDL_Texture* texture, int tile_size, Relay *relay);

        ~EnemyManager();
        EnemyManager(const EnemyManager& other) = delete;
        EnemyManager& operator=(const EnemyManager&) = delete;

        void AddEnemy(Enemy *enemy);
        void MakeEnemyOne(int x = 1, int y = 1);
        void MakeEnemyTwo(int x = 1, int y = 1);
        void MakeEnemyThree(int x = 1, int y = 1);
        void Draw(SDL_Renderer* renderer) const;
        void Update();
        void KillEnemies(int x, int y, double intensity);

    protected:

    private:
        int m_enemies_numb;
        list<Enemy*> m_enemies;
        Relay* m_relay;
        int m_tile_size;
};

#endif // ENEMY_MANAGER_H
