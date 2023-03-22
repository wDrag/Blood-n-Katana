#ifndef TIMER_H
#define TIMER_H

#include <chrono>

const int TARGET_FPS = 60;
const int TARGET_DELTATIME = 1.5f;

class Timer{
    public:
        static Timer* getInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();}
        void Tick();
        inline float getDeltaTime(){return m_DeltaTime;}

    private:
        static Timer* s_Instance;
        std::chrono::high_resolution_clock::time_point m_StartTime;
        std::chrono::duration<float> m_DeltaTime;
};

#endif