#ifndef BOMB_MANAGER_H
#define BOMB_MANAGER_H

#include <list>
#include <SDL_mixer.h>
#include "../Display/DisplayElement.h"
#include "../Entity/Bomb.h"
#include "../System/Relay.h"

using namespace std;

class BombManager : public DisplayElement {
    public:
        BombManager(SDL_Texture* texture, int tile_size, Relay* relay);

        ~BombManager();
        BombManager(const BombManager& other) = delete;
        BombManager& operator=(const BombManager&) = delete;

        void AddBomb(Bomb *bomb);
        void MakeBomb(int fuse_duration, int x, int y, int player_id, double intensity = 1.0, int damage = 25);
        void Update();
        void Draw(SDL_Renderer* renderer) const;

    protected:

    private:
        list<Bomb*> m_bombs;
        int m_bomb_size, m_tile_size;
        Relay* m_relay;
        Mix_Chunk* m_bomb_sound_effect;
};

#endif // BOMB_MANAGER_H

