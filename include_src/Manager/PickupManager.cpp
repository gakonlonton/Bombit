#include "../../include/Manager/PickupManager.h"

using namespace std;

PickUpManager::PickUpManager(SDL_Texture* texture, int tile_size, Relay* relay)
    : DisplayElement(texture), m_tile_size(tile_size), m_draw_size(tile_size*3/4), m_relay(relay) { }

PickUpManager::Iterator::Iterator(PickUpManager* pickup_manager)
    : m_pickups_pointer(&(pickup_manager->m_pickups)), it(m_pickups_pointer->begin()) { }

PickUpManager::~PickUpManager() {
    for(auto i = m_pickups.begin(); i != m_pickups.end(); i++) {
        delete (*i);
    }
}

void PickUpManager::AddPickUp(PickUp* pickup) {
    m_pickups.push_back(pickup);
}

void PickUpManager::MakePickUp(PickUp::PickUpType type, int x, int y, int value) {
    PickUp* pickup = new PickUp(d_texture, type, value, x, y, m_draw_size);
    AddPickUp(pickup);
}

void PickUpManager::Update(void) {
    for(auto i = m_pickups.begin(); i != m_pickups.end();) {
        if((*i)->IsUsed()) {
            delete (*i);
            i = m_pickups.erase(i);
        }
        else i++;
    }
}

void PickUpManager::Draw(SDL_Renderer* renderer) const {
    for(auto i = m_pickups.begin(); i != m_pickups.end(); i++) {
        (*i)->Draw(renderer);
    }
}

void PickUpManager::Iterator::Reset() {
    it = m_pickups_pointer->begin();
}

bool PickUpManager::Iterator::Finished() const {
    return Current() == End();
}

PickUp& PickUpManager::Iterator::GetPickUp() const {
    return **it;
}

PickUpManager::Iterator& PickUpManager::Iterator::operator++() {
    Next();
    return *this;
}

list<PickUp*>::iterator PickUpManager::Iterator::Begin() const {
    return m_pickups_pointer->begin();
}

list<PickUp*>::iterator PickUpManager::Iterator::End() const {
    return m_pickups_pointer->end();
}

list<PickUp*>::iterator PickUpManager::Iterator::Current() const {
     return it;
}

list<PickUp*>::iterator PickUpManager::Iterator::Next() {
    if(it == End()) return it;
    else return ++it;
}

