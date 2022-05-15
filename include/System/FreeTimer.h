#ifndef FREE_TIMER_H
#define FREE_TIMER_H

class FreeTimer {
    public:
        FreeTimer();
        void ResetTimer();
        void DecreaseTimer(long long interval);
        void Pause();
        void Unpause();
        bool IsPaused() const;
        long long GetTimeElapsed() const;

    protected:

    private:
        long long m_past_ticks;
        long long m_paused_ticks;
        bool m_paused;

};

#endif // FREE_TIMER_H

