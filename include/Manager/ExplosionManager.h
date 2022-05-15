#ifndef EXPLOSION_MANAGER_H
#define EXPLOSION_MANAGER_H

#include <list>
#include "../Display/DisplayElement.h"
#include "../Entity/Explosion.h"

using namespace std;

class ExplosionManager : public DisplayElement {
    public:
        ExplosionManager(SDL_Texture* texture, int tile_size);

        ~ExplosionManager();
        ExplosionManager(const ExplosionManager& other) = delete;
        ExplosionManager& operator=(const ExplosionManager&) = delete;

        void AddExplosion(Explosion *explosion);
        void MakeExplosion(int duration, int x_center, int y_center, double intensity);
        void Update();
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        list<Explosion*> m_explosions;
        int m_tile_size;
};

#endif // EXPLOSION_MANAGER_H

