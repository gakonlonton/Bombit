#include "../../include/Display/DisplayGame.h"
#include "../../include/Display/PauseDisplay.h"
#include "../../include/System/Timer.h"
#include "../../include/System/Relay.h"
#include "../../include/Manager/MapManager.h"
#include "../../include/Manager/BombManager.h"
#include "../../include/Manager/ExplosionManager.h"
#include "../../include/Manager/PlayerManager.h"
#include "../../include/Manager/EnemyManager.h"
#include "../../include/Manager/PickupManager.h"
#include "../../include/Constant/Resources.h"
#include "../../include/Constant/WindowConstant.h"
#include <bits/stdc++.h>

using namespace std;

GameDisplay::GameDisplay(SDL_Texture* texture, SDL_Renderer* renderer, int windowWidth, int windowHeight, int players_number, int current_level, int number_of_screen_elements)
    : Display(), d_texture(texture), d_renderer(renderer), d_windowWidth(windowWidth), d_windowHeight(windowHeight), m_players_number(players_number), d_current_level(current_level), d_level_completed(false), m_music(nullptr) {

    d_displayElements.reserve(number_of_screen_elements);
    Timer::Instance()->Pause();

    int tile_size = MAP_TILE_SIZE;
    m_relay = new Relay();

    string level_num;
    stringstream convert;
    convert << d_current_level;
    level_num = convert.str();

    string path_level = RESOURCE_BASE + RESOURCE_LEVEL_MAP + level_num + RESOURCE_LEVEL_MAP_EXT;
    string path_player = RESOURCE_BASE + RESOURCE_LEVEL_PLAYER + level_num + RESOURCE_LEVEL_PLAYER_EXT;
    string path_enemy = RESOURCE_BASE + RESOURCE_LEVEL_ENEMY + level_num + RESOURCE_LEVEL_ENEMY_EXT;
    Map* level = new Map(path_level, d_texture, tile_size, m_relay);
    ExplosionManager* explosion_manager = new ExplosionManager(d_texture, tile_size);
    BombManager* bomb_manager = new BombManager(d_texture, tile_size, m_relay);
    PlayerManager* player_manager = new PlayerManager(path_player, d_texture, tile_size, m_relay, m_players_number);
    if(m_players_number > 1) {
        player_manager->GetPlayerById(1)->SetKeycodes(SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_g);
    }
    EnemyManager* enemy_manager = new EnemyManager(path_enemy, d_texture, tile_size, m_relay);
    PickUpManager* pickup_manager = new PickUpManager(d_texture, tile_size, m_relay);

    m_relay->SetExplosionManager(explosion_manager);
    m_relay->SetBombManager(bomb_manager);
    m_relay->SetPlayerManager(player_manager);
    m_relay->SetEnemyManager(enemy_manager);
    m_relay->SetMap(level);
    m_relay->SetPickUpManager(pickup_manager);

    AddDisplayElement(level);
    AddDisplayElement(pickup_manager);
    AddDisplayElement(bomb_manager);
    AddDisplayElement(player_manager);
    AddDisplayElement(enemy_manager);
    AddDisplayElement(explosion_manager);

    string path_music = RESOURCE_BASE + RESOURCE_MUSIC;
    m_music = Mix_LoadMUS(path_music.c_str());
}

GameDisplay::~GameDisplay() {
    for(auto i = d_displayElements.begin(); i != d_displayElements.end(); i++) {
        delete (*i);
    }

    d_displayElements.clear();
    delete m_relay;
}

void GameDisplay::AddDisplayElement(DisplayElement* display_element) {
    d_displayElements.push_back(display_element);
}

void GameDisplay::Init(void) {
    Mix_PlayMusic(m_music, -1);
    Timer::Instance()->Unpause();
}

void GameDisplay::Enter(int mode) {
    Mix_ResumeMusic();
    Timer::Instance()->Unpause();
    d_leaveNext = false;
    if(mode == 0) {
        d_leavePrevious = true;
    }
    else d_leavePrevious = false;
}

void GameDisplay::Leave(void) {
    Mix_PauseMusic();
    Timer::Instance()->Pause();
}

int GameDisplay::Destroy(void) {
    Mix_PauseMusic();
    Mix_FreeMusic(m_music);

    for(auto i = d_displayElements.begin(); i != d_displayElements.end(); i++) {
        delete (*i);
    }

    d_displayElements.clear();
    delete m_relay;
    if(d_level_completed) return ++d_current_level;
    else return 0;
}

void GameDisplay::Update(void) {
    if(m_relay->PlayersDead()) {
        d_leavePrevious = true;
        d_level_completed = false;
    }
    else if(m_relay->LevelCompleted()) {
        d_leavePrevious = true;
        d_level_completed = true;
    }
    else if (d_keyboardInput->IsKeyOn(SDLK_ESCAPE)) {
        d_leaveNext = true;
        d_nextDisplay = new PauseDisplay(d_renderer, d_windowWidth, d_windowHeight);
    }
    else {
        for(auto i = d_displayElements.begin(); i != d_displayElements.end(); i++) {
            (*i)->Update();
        }
    }
}

void GameDisplay::Draw(SDL_Renderer* renderer) const {
    for (auto i = d_displayElements.cbegin(); i != d_displayElements.cend(); i++) {
        (*i)->Draw(renderer);
    }
}
