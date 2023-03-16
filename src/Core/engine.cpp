#include "Core/engine.h"
#include "Graphics/TextureManager.h"
#include "Physics/Transform.h"
#include "Characters/Samurai.h"

Engine* Engine::s_Instance = nullptr;
Samurai* player = nullptr;

bool Engine::Init(){
    if (SDL_Init(SDL_INIT_VIDEO)!= 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("BND", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_Window == nullptr){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr){
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    TextureManager::getInstance()->Load("src/resources/Samurai/Attack_1.png", "player");
    player = new Samurai(new Properties("player", 128, 128, 100, 100));
    return m_isRunning = true;
}

void Engine::Clean(){
    TextureManager::getInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit(){
    m_isRunning = false;
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Update(){
    player -> Update(0);
}
void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 203, 195, 227, 255);
    SDL_RenderClear(m_Renderer);
    // TextureManager::getInstance() -> Draw("player", 100, 100, 128, 128);
    player -> Draw();
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
