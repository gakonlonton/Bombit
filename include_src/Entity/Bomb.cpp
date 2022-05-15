#include "../../include/Entity/Bomb.h"
#include "../../include/Constant/BombTexture.h"

Bomb::Bomb(int fuse_duration, SDL_Texture* texture, int x, int y, int bomb_size, double intensity, int damage)
    :   m_timer(), m_fuse_duration(fuse_duration), m_texture(texture), m_explode(false), m_x(x), m_y(y),
        m_draw_size(bomb_size), m_intensity(intensity), m_phase_number(0), m_damage(damage) { }

void Bomb::Update(void) {
    if(m_timer.GetTimeElapsed() > m_fuse_duration) m_explode = true;
    else {
        m_phase_number =  m_timer.GetTimeElapsed()/(m_fuse_duration/BOMB_TEXTURE_COUNT);
    }
}

bool Bomb::Explode() const {
    return m_explode;
}

void Bomb::Draw(SDL_Renderer* renderer) const {
    SDL_Rect SrcR;
    SDL_Rect DestR;

    SrcR.h = BOMB_TEXTURE_H;
    SrcR.w = BOMB_TEXTURE_W;
    SrcR.x = BOMB_TEXTURE_X + m_phase_number*BOMB_TEXTURE_OF_X;
    SrcR.y = BOMB_TEXTURE_Y + m_phase_number*BOMB_TEXTURE_OF_Y;

    DestR.h = m_draw_size;
    DestR.w = m_draw_size;
    DestR.x = m_x - m_draw_size/2;
    DestR.y = m_y - m_draw_size/2;

    SDL_RenderCopy(renderer, m_texture, &SrcR, &DestR);
}

