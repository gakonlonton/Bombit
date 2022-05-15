#include "../../include/System/UltiTimer.h"
#include <SDL.h>

using namespace std;

UTimer::UTimer(void)
    : m_system_timer(Timer::Instance()),
      m_past_ticks(m_system_timer->GetTimeElapsed()),
      m_paused_ticks(m_past_ticks),
      m_paused(false) { }

UTimer::UTimer(Timer* system_timer)
    : m_system_timer(system_timer),
      m_past_ticks(m_system_timer->GetTimeElapsed()),
      m_paused_ticks(m_past_ticks),
      m_paused(false) { }

void UTimer::ResetTimer(void) {
    m_past_ticks = m_system_timer->GetTimeElapsed();
}

void UTimer::DecreaseTimer(long long interval) {
    m_past_ticks += interval;
}

long long UTimer::GetTimeElapsed() const {
    if(m_paused) return m_paused_ticks - m_past_ticks;
    else return m_system_timer->GetTimeElapsed() - m_past_ticks;
}

void UTimer::Pause(void) {
    if(!m_paused) {
        m_paused_ticks = m_system_timer->GetTimeElapsed();
        m_paused = true;
    }
}

void UTimer::Unpause(void) {
    if(m_paused) {
        m_past_ticks = m_system_timer->GetTimeElapsed() - (m_paused_ticks - m_past_ticks);
        m_paused = false;
    }
}

bool UTimer::IsPaused(void) const {
    return m_paused;
}

