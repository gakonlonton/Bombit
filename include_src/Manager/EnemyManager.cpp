#include <fstream>
#include <iostream>
#include "../../include/Manager/EnemyManager.h"
#include "../../include/Manager/PlayerManager.h"
#include "../../include/Entity/Player.h"
#include "../../include/Destroyer/Destroyer.h"
#include "../../include/Entity/EnemyList.h"

using namespace std;

EnemyManager::EnemyManager(string path_to_file, SDL_Texture* texture, int tile_size, Relay *relay) : DisplayElement(texture) {
    d_texture = texture;
    m_tile_size = tile_size;
    m_relay = relay;

    fstream fs;
    fs.open (path_to_file, fstream::in);
    if (!fs.is_open()) exit(EXIT_FAILURE);
    fs >> m_enemies_numb;

    for(int i = 0; i < m_enemies_numb; i++) {
        int type, x = 0, y = 0;
        fs >> type >> x >> y;
        switch(type) {
            case 1:
                MakeEnemyOne(x, y);
                break;
            case 2:
                MakeEnemyTwo(x, y);
                break;
            case 3:
                // MakeEnemyThree(x, y);
                MakeEnemyTwo(x, y);
                break;
            default:
                break;
        }
    }

    fs.close();
}

EnemyManager::~EnemyManager(void) {
    for(auto i = m_enemies.begin(); i != m_enemies.end(); i++) {
        delete (*i);
    }
}

void EnemyManager::KillEnemies(int x, int y, double intensity) {
    for(auto i = m_enemies.begin(); i != m_enemies.end(); ) {
        Destroyer::DestroyEnemy(*i, x, y, m_tile_size, intensity);
        if((*i)->GetHealth() == 0) {
            delete (*i);
            i = m_enemies.erase(i);
        }
        else i++;
    }
}

void EnemyManager::AddEnemy(Enemy *enemy) {
    m_enemies.push_back(enemy);
}

void EnemyManager::MakeEnemyOne(int x, int y) {
    Enemy* e = new EnemyOne(d_texture, m_tile_size, x, y);
    AddEnemy(e);
}

void EnemyManager::MakeEnemyTwo(int x, int y) {
    Enemy* e = new EnemyTwo(d_texture, m_tile_size, x, y);
    AddEnemy(e);
}

void EnemyManager::MakeEnemyThree(int x, int y) {
    Enemy* e = new EnemyThree(d_texture, m_tile_size, x, y);
    AddEnemy(e);
}

void EnemyManager::Draw(SDL_Renderer* renderer) const {
    for(auto i = m_enemies.begin(); i != m_enemies.end(); i++) {
        (*i)->Draw(renderer);
    }
}

void EnemyManager::Update(void) {
    for(auto i = m_enemies.begin(); i != m_enemies.end(); i++) {
        (*i)->Update(m_relay);
    }
}

