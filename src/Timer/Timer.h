#ifndef TIMER_H
#define TIMER_H

#include <chrono>

const int TARGET_FPS = 60;
const int TARGET_DELTATIME = 15.0f;

class Timer{
    public:
        static Timer* getInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();}
        void Tick();
        inline float getDeltaTime(){return m_DeltaTime;}

    private:
        static Timer* s_Instance;
        float m_StartTime = 0.0f;
        float m_DeltaTime = 0.0f;
};

#endif