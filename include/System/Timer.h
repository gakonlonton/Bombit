#ifndef TIMER_H
#define TIMER_H

class Timer {
    public:
        static Timer* Instance();
        long long GetTimeElapsed() const;
        void Pause();
        void Unpause();
        bool IsPaused() const;

    protected:
        Timer();

    private:
        long long m_past_ticks, m_paused_ticks;
        bool  m_paused;
        static Timer* s_instance;
        void ResetTimer();
        void DecreaseTimer(long long interval);
};

#endif // TIMER_H

