#include "../../include/Entity/DestructibleWall.h"
#include "../../include/Constant/MapObjectTexture.h"

DestructibleWall::DestructibleWall(SDL_Texture *texture, int kind)
    : MapObject(MapObject::DESTRUCTIBLE_WALL, texture, kind), m_integrity(S_MAX_INTEGRITY) { }

bool DestructibleWall::IsDestroyed() const {
    if(m_integrity <= 0) return true;
    else return false;
}

void DestructibleWall::DecreaseIntegrity(int value) {
    m_integrity -= value;
    if(m_integrity < 0) m_integrity = 0;
}

void DestructibleWall::Draw(SDL_Renderer* renderer, const SDL_Rect *DestR) {
    SDL_Rect SrcR;
    int integrity_level = (S_MAX_INTEGRITY - m_integrity)/(S_MAX_INTEGRITY/TEXTURE_MAP_DESTRUCTIBLE_INTEG_COUNT);
    integrity_level = min2(integrity_level, TEXTURE_MAP_DESTRUCTIBLE_INTEG_COUNT - 1);

    SrcR.h = TEXTURE_MAP_DESTRUCTIBLE_H;
    SrcR.w = TEXTURE_MAP_DESTRUCTIBLE_W;
    SrcR.x = TEXTURE_MAP_DESTRUCTIBLE_X + TEXTURE_MAP_DESTRUCTIBLE_OF_X * m_kind + TEXTURE_MAP_DESTRUCTIBLE_INTEG_OF_X*integrity_level;
    SrcR.y = TEXTURE_MAP_DESTRUCTIBLE_Y + TEXTURE_MAP_DESTRUCTIBLE_OF_Y * m_kind + TEXTURE_MAP_DESTRUCTIBLE_INTEG_OF_Y*integrity_level;

    SDL_RenderCopy(renderer, m_texture, &SrcR, DestR);
}


