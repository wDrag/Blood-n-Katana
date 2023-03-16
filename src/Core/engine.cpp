#include "Core/engine.h"
#include <iostream>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init(){
    if (SDL_Init(SDL_INIT_VIDEO)!= 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow("BND", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_Window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return m_isRunning = true;
}

bool Engine::Clean(){
    return false;
}

void Engine::Quit(){
    m_isRunning = false;
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Update(){

}
void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderPresent(m_Renderer);
}
void Engine::Events(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                Quit();
                break;
            default:
                break;
        }
    }

}
