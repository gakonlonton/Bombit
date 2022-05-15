#ifndef PICKUP_MANAGER_H
#define PICKUP_MANAGER_H

#include "../Display/DisplayElement.h"
#include "../System/Relay.h"
#include "../Entity/Pickup.h"
#include <bits/stdc++.h>

using namespace std;

class PickUpManager : public DisplayElement {
    public:

        PickUpManager(SDL_Texture* texture, int tile_size, Relay* relay);

        ~PickUpManager();
        PickUpManager(const PickUpManager& other) = delete;
        PickUpManager& operator=(const PickUpManager&) = delete;

        void AddPickUp(PickUp* pickup);
        void MakePickUp(PickUp::PickUpType type, int x, int y, int value = 0);
        void Update();
        void Draw(SDL_Renderer* renderer) const;
        class Iterator {
            public:
                Iterator(PickUpManager* pickup_manager);
                void Reset();
                bool Finished() const;
                PickUp& GetPickUp() const;
                Iterator& operator++ ();

            private:
                list<PickUp*>* m_pickups_pointer;
                list<PickUp*>::iterator it;
                inline list<PickUp*>::iterator Begin() const;
                inline list<PickUp*>::iterator End() const;
                inline list<PickUp*>::iterator Current() const;
                inline list<PickUp*>::iterator Next();
        };
    protected:

    private:
        list<PickUp*> m_pickups;
        int m_tile_size, m_draw_size;
        Relay* m_relay;
};

#endif // PICKUP_MANAGER_H
