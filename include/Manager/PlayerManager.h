#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include <SDL.h>
#include <vector>
#include "../Display/DisplayElement.h"
#include "../Entity/Player.h"
#include "../System/UltiTimer.h"
#include "../System/Relay.h"
#include "SDL_mixer.h"

using namespace std;

class PlayerManager : public DisplayElement {
    public:
        PlayerManager(string path_to_file, SDL_Texture* texture, int tile_size, Relay *relay, int numb_of_players_to_load = 2);

        ~PlayerManager();
        PlayerManager(const PlayerManager& other) = delete;
        PlayerManager& operator=(const PlayerManager&) = delete;

        Player* GetPlayerById(int id);
        bool AreDead() const;
        bool AreCompleted() const;
        void AddPlayer(Player *player);
        void MakePlayer(int player_id = 0, int x = 1, int y = 1);
        void Draw(SDL_Renderer* renderer) const;
        void DrawScore(SDL_Renderer* renderer, int player_id, int lives) const;
        void Update();
        void KillPlayer(int x, int y, double intensity);
        class Iterator {
            public:
                Iterator(PlayerManager* player_manager);
                void Reset();
                bool Finished() const;
                Player& GetPlayer() const;
                Iterator& operator++ ();

            private:
                vector<Player*>* m_players_pointer;
                vector<Player*>::iterator it;
                inline vector<Player*>::iterator Begin() const;
                inline vector<Player*>::iterator End() const;
                inline vector<Player*>::iterator Current() const;
                inline vector<Player*>::iterator Next();
        };

    protected:

    private:
        int m_death_time, m_players_numb, m_numb_of_players_to_load;
        UTimer m_timer;
        vector<Player*> m_players;
        Relay* m_relay;
        int m_tile_size;
        Mix_Chunk* m_kill_sound;
};

#endif // PLAYER_MANAGER_H
