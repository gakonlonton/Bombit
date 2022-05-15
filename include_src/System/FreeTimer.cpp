#include "../../include/System/FreeTimer.h"
#include <SDL.h>

FreeTimer::FreeTimer(void)
         : m_past_ticks(SDL_GetTicks()),
           m_paused_ticks(m_past_ticks),
           m_paused(false) {}

void FreeTimer::ResetTimer(void) {
    m_past_ticks = SDL_GetTicks();
}

void FreeTimer::DecreaseTimer(long long interval) {
    m_past_ticks += interval;
}

long long FreeTimer::GetTimeElapsed() const {
    if(m_paused) return m_paused_ticks - m_past_ticks;
    else return SDL_GetTicks() - m_past_ticks;
}

void FreeTimer::Pause(void) {
    if(m_paused == false) {
        m_paused_ticks = SDL_GetTicks();
        m_paused = true;
    }
}

void FreeTimer::Unpause(void) {
    if(m_paused) {
        m_past_ticks = SDL_GetTicks() - (m_paused_ticks - m_past_ticks);
        m_paused = false;
    }
}

bool FreeTimer::IsPaused(void) const {
    return m_paused;
}

