#include "../../include/Manager/BombManager.h"
#include "../../include/Manager/PlayerManager.h"
#include "../../include/Constant/Resources.h"
#include "../../include/Destroyer/Wall.h"
#include "../../include/Manager/ExplosionManager.h"
#include "../../include/Manager/EnemyManager.h"
#include "../../include/Constant/ExplosionTexture.h"
#include "../../include/Constant/BombTexture.h"

using namespace std;

BombManager::BombManager(SDL_Texture* texture, int tile_size, Relay* relay)
    : DisplayElement(texture), m_bomb_size(tile_size*BOMB_SIZE_TO_TILE), m_tile_size(tile_size), m_relay(relay) {
    string path_music = RESOURCE_BASE + RESOURCE_EXPLOSION_LOAD;
    m_bomb_sound_effect = Mix_LoadWAV(path_music.c_str());
}

BombManager::~BombManager(void) {
    Mix_FreeChunk(m_bomb_sound_effect);
    for(auto i = m_bombs.begin(); i != m_bombs.end(); i++) {
        delete (*i);
    }
}

void BombManager::AddBomb(Bomb *bomb) {
    m_bombs.push_back(bomb);
}

void BombManager::MakeBomb(int fuse_duration, int x, int y, int player_id, double intensity, int damage) {
    Bomb* b = new Bomb(fuse_duration, d_texture, x, y, m_bomb_size, player_id, intensity, damage);
    AddBomb(b);
}

void BombManager::Update(void) {
    for(auto i = m_bombs.begin(); i != m_bombs.end(); ) {
        (*i)->Update();
        if((*i)->Explode()) {
            Mix_PlayChannel(-1, m_bomb_sound_effect, 0);
            m_relay->GetExplosionManager()->MakeExplosion(EXPLOSION_ANIMATION_LENGTH, (*i)->GetX(), (*i)->GetY(), (*i)->GetIntensity());
            WallDestroyer wd(m_relay->GetMap(), (*i)->GetX(), (*i)->GetY(), m_tile_size, (*i)->GetIntensity(), (*i)->GetDamage());
            m_relay->GetEnemyManager()->KillEnemies((*i)->GetX(), (*i)->GetY(), (*i)->GetIntensity());
            m_relay->GetPlayerManager()->KillPlayer((*i)->GetX(), (*i)->GetY(), (*i)->GetIntensity());
            m_relay->GetPlayerManager()->GetPlayerById((*i)->GetPlayerId())->DecreaseTempBombNumber();
            delete (*i);
            i = m_bombs.erase(i);
        }
        else i++;
    }
}

void BombManager::Draw(SDL_Renderer* renderer) const {
    for(auto i = m_bombs.begin(); i != m_bombs.end(); i++) {
        (*i)->Draw(renderer);
    }
}

