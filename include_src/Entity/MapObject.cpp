#include "../../include/Entity/MabObject.h"
#include "../../include/Constant/MapObjectTexture.h"

MapObject::MapObject(Tile id, SDL_Texture *texture, int kind)
    : m_id(id), m_texture(texture), m_kind(kind) { }

void MapObject::Draw(SDL_Renderer* renderer, const SDL_Rect *DestR) {
    SDL_Rect SrcR;
    if(m_id == EMPTY) {
        SrcR.h = TEXTURE_MAP_EMPTY_H;
        SrcR.w = TEXTURE_MAP_EMPTY_W;
        SrcR.x = TEXTURE_MAP_EMPTY_X + TEXTURE_MAP_EMPTY_OF_X * m_kind;
        SrcR.y = TEXTURE_MAP_EMPTY_Y + TEXTURE_MAP_EMPTY_OF_Y * m_kind;
    }
    else {
        SrcR.h = TEXTURE_MAP_INDESTRUCTIBLE_H;
        SrcR.w = TEXTURE_MAP_INDESTRUCTIBLE_W;
        SrcR.x = TEXTURE_MAP_INDESTRUCTIBLE_X + TEXTURE_MAP_INDESTRUCTIBLE_OF_X * m_kind;
        SrcR.y = TEXTURE_MAP_INDESTRUCTIBLE_Y + TEXTURE_MAP_INDESTRUCTIBLE_OF_Y * m_kind;
    }

    SDL_RenderCopy(renderer, m_texture, &SrcR, DestR);
}

