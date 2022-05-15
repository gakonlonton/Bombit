#include "../../include/Entity/Explosion.h"
#include "../../include/Constant/ExplosionTexture.h"

Explosion::Explosion(int duration, int x_center, int y_center, double intensity, int tile_size, SDL_Texture* texture)
    :   m_timer(), m_duration(duration), m_exploding(true), m_x_center(x_center), m_y_center(y_center),
        m_intensity(intensity), m_tile_size(tile_size), m_texture(texture), m_phase_number(0) { }

void Explosion::Update(void) {
    if(m_timer.GetTimeElapsed() > m_duration) m_exploding = false;
    else {
        m_phase_number = m_timer.GetTimeElapsed()/(m_duration/TEXTURE_EXPLOSION_COUNT);
        m_phase_number = min2(m_phase_number, TEXTURE_EXPLOSION_COUNT - 1);
    }
}

bool Explosion::IsExploding() const {
    return m_exploding;
}

void Explosion::Draw(SDL_Renderer* renderer) const {
    SDL_Rect SrcR;
    SDL_Rect DestR;
    int explosion_size = m_tile_size * m_intensity;
    int number_in_line = m_phase_number % TEXTURE_EXPLOSION_LINE_COUNT;
    int line_number = m_phase_number / TEXTURE_EXPLOSION_LINE_COUNT;

    SrcR.h = TEXTURE_EXPLOSION_H;
    SrcR.w = TEXTURE_EXPLOSION_W;
    SrcR.x = TEXTURE_EXPLOSION_X + TEXTURE_EXPLOSION_LINE_OFFSET_X * line_number + TEXTURE_EXPLOSION_OFFSET_X * number_in_line;
    SrcR.y = TEXTURE_EXPLOSION_Y + TEXTURE_EXPLOSION_LINE_OFFSET_Y * line_number + TEXTURE_EXPLOSION_OFFSET_Y * number_in_line;

    DestR.h = explosion_size;
    DestR.w = explosion_size;
    DestR.x = m_x_center - explosion_size / 2;
    DestR.y = m_y_center - explosion_size / 2;

    SDL_RenderCopy(renderer, m_texture, &SrcR, &DestR);
}


