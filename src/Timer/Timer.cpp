#include "Timer/Timer.h"

#include <SDL2/SDL.h>

Timer* Timer::s_Instance = nullptr;

void Timer::Tick(){
    m_DeltaTime = (SDL_GetTicks() - m_StartTime) * (TARGET_FPS/1000.0f);
    SDL_Log("%f", m_DeltaTime);
    while (m_DeltaTime > TARGET_DELTATIME)
        m_DeltaTime -= TARGET_DELTATIME;

    m_StartTime = SDL_GetTicks();
}