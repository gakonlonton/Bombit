#include "../../include/Manager/PlayerManager.h"
#include "../../include/Destroyer/Destroyer.h"
#include "../../include/Constant/ScoreConstant.h"
#include "../../include/Constant/Resources.h"
#include <fstream>
#include <cstdlib>

using namespace std;

PlayerManager::PlayerManager(string path_to_file, SDL_Texture* texture, int tile_size, Relay *relay)
    : DisplayElement(texture) {
    m_tile_size = tile_size;
    m_relay = relay;
    m_timer.ResetTimer();
    fstream fs;
    fs.open(path_to_file, fstream::in);

    if(!fs.is_open()) exit(0);
    int id, x = 0, y = 0;
    fs >> id >> x >> y;
    MakePlayer(x, y);
    fs.close();
    string path_music = RESOURCE_BASE + RESOURCES_KILL_LOAD;
    m_kill_sound = Mix_LoadWAV(path_music.c_str());
}

PlayerManager::~PlayerManager() {
    Mix_FreeChunk(m_kill_sound);
    for(auto i = m_players.begin(); i != m_players.end(); ++i) {
        delete (*i);
    }
}

void PlayerManager::MakePlayer(int x, int y) {
    Player *player = new Player(d_texture, m_tile_size, m_relay, x, y);
    m_players.push_back(player);
}

void PlayerManager::KillPlayer(int x, int y, double intensity) {
    for(auto i = m_players.begin(); i != m_players.end(); ++i) {
        Destroyer::DestroyPlayer(*i, x, y, m_tile_size, intensity);
    }
}

void PlayerManager::AddPlayer(Player *player) {
    m_players.push_back(player);
}

void PlayerManager::DrawScore(SDL_Renderer* renderer, int lives) const {
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.y = TEXTURE_NUMB_Y;
    SrcR.w = TEXTURE_NUMB_SOURCE_W;
    SrcR.h = TEXTURE_NUMB_SOURCE_H;

    SrcR.x = lives*TEXTURE_NUMB_SOURCE_W + TEXTURE_NUMB_X;

    DestR.x = 0 + 2*m_tile_size;
    DestR.y = 0;
    DestR.w = m_tile_size;
    DestR.h = m_tile_size;

    SDL_RenderCopy(renderer, d_texture, &SrcR, &DestR);

}

void PlayerManager::Draw(SDL_Renderer* renderer) const {
    for(auto i = m_players.begin(); i != m_players.end(); ++i) {
        DrawScore(renderer, (*i)->GetLives());
        if(((*i)->GetLives() != 0) and !((*i)->IsLevelCompleted())) (*i)->Draw(renderer);
    }
}

void PlayerManager::Update() {
    for(auto i = m_players.begin(); i != m_players.end(); ++i) {
        auto val = (*i);
        if(val->GetHealth() == 0) {
            Mix_PlayChannel(-1, m_kill_sound, 0);
            val->SetAlive(0);
            int lives = val->GetLives();
            if(--lives < 0) lives = 0;
            val->SetLives(lives);
        }
        if(val->GetAlive() == 0) {
            val->SetX(-1);
            val->SetY(-1);
            val->SetHealth(100);
            val->SetAlive(1);
        }

        if((val->GetLives() != 0) and !(val->IsLevelCompleted())) val->Update();
    }
}

Player* PlayerManager::GetPlayerById(int id) {
    return m_players[id];
}

bool PlayerManager::AreDead() const {
    for(auto i = m_players.begin(); i != m_players.end(); ++i) {
        if((*i)->GetLives() != 0) return false;
    }
    return true;
}

bool PlayerManager::AreCompleted() const {
    bool finished = false;
    for(auto i = m_players.begin(); i != m_players.end(); ++i) {
        if(!(*i)->IsLevelCompleted() and (*i)->GetLives() != 0) return false;
        else if((*i)->IsLevelCompleted()) finished = true;
    }
    return finished;

}

PlayerManager::Iterator::Iterator(PlayerManager* player_manager)
    : m_players_pointer(&(player_manager->m_players)),
      it (m_players_pointer->begin())
{
}

void PlayerManager::Iterator::Reset() {
    it = m_players_pointer->begin();
}

bool PlayerManager::Iterator::Finished() const {
    return Current() == End();
}

Player& PlayerManager::Iterator::GetPlayer() const {
    return **it;
}

PlayerManager::Iterator& PlayerManager::Iterator::operator++() {
    Next();
    return *this;
}

vector<Player*>::iterator PlayerManager::Iterator::Begin() const {
    return m_players_pointer->begin();
}

vector<Player*>::iterator PlayerManager::Iterator::End() const {
    return m_players_pointer->end();
}

vector<Player*>::iterator PlayerManager::Iterator::Current() const {
     return it;
}

vector<Player*>::iterator PlayerManager::Iterator::Next() {
    if(it == End()) return it;
    else return ++it;
}
