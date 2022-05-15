#include "../../include/Manager/ExplosionManager.h"

ExplosionManager::ExplosionManager(SDL_Texture* texture, int tile_size) : DisplayElement(texture), m_tile_size(tile_size)
{ }

ExplosionManager::~ExplosionManager(void) {
    for(auto i = m_explosions.begin(); i != m_explosions.end(); ++i) {
        delete (*i);
    }
}

void ExplosionManager::AddExplosion(Explosion *explosion) {
    m_explosions.push_back(explosion);
}

void ExplosionManager::MakeExplosion(int duration, int x_center, int y_center, double intensity) {
    Explosion* e = new Explosion(duration, x_center, y_center, intensity, m_tile_size, d_texture);
    AddExplosion(e);
}

void ExplosionManager::Update(void) {
    for(auto i = m_explosions.begin(); i != m_explosions.end(); ) {
        (*i)->Update();
        if(!((*i)->IsExploding())) {
            delete (*i);
            i = m_explosions.erase(i);
        }
        else i++;
    }
}

void ExplosionManager::Draw(SDL_Renderer* renderer) const {
    for(auto i = m_explosions.begin(); i != m_explosions.end(); i++) {
        (*i)->Draw(renderer);
    }
}

