#include "../../include/System/Timer.h"
#include <SDL.h>

Timer* Timer::s_instance;

Timer::Timer(void)
    : m_past_ticks(SDL_GetTicks()),
      m_paused_ticks(m_past_ticks),
      m_paused(false) {}

Timer* Timer::Instance(void) {
    if(s_instance == 0) {
        s_instance = new Timer();
    }
    return s_instance;
}

void Timer::ResetTimer(void) {
    m_past_ticks = SDL_GetTicks();
}

void Timer::DecreaseTimer(long long interval) {
    m_past_ticks += interval;
}

long long Timer::GetTimeElapsed() const {
    if(m_paused) return m_paused_ticks - m_past_ticks;
    else return SDL_GetTicks() - m_past_ticks;
}

void Timer::Pause(void) {
    if(!m_paused) {
        m_paused_ticks = SDL_GetTicks();
        m_paused = true;
    }
}

void Timer::Unpause(void) {
    if(m_paused) {
        m_past_ticks = SDL_GetTicks() - (m_paused_ticks - m_past_ticks);
        m_paused = false;
    }
}

bool Timer::IsPaused() const {
    return m_paused;
}

