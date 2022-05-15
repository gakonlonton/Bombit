#ifndef UTIMER_H
#define UTIMER_H

#include "Timer.h"

class UTimer {
    public:
        UTimer();
        UTimer(Timer* system_timer);
        void ResetTimer();
        void DecreaseTimer(long long interval);
        long long GetTimeElapsed() const;
        void Pause();
        void Unpause();
        bool IsPaused() const;

    protected:

    private:
        Timer* m_system_timer;
        long long m_past_ticks, m_paused_ticks;
        bool m_paused;

};

#endif // UTIMER_H

