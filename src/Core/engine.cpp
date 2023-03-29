#include "Core/engine.h"
#include "Graphics/TextureManager.h"
#include "Physics/Transform.h"
#include "Characters/Samurai.h"
#include "Inputs/Input.h"
#include "Timer/Timer.h"

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
    TextureManager::getInstance() -> Load("src/resources/Samurai/Idle.png", "player_Idle");
    TextureManager::getInstance() -> Load("src/resources/Samurai/Walk.png", "player_Walk");
    TextureManager::getInstance() -> Load("src/resources/Samurai/Run.png", "player_Run");
    TextureManager::getInstance() -> Load("src/resources/Samurai/Attack_1.png", "player_Attack1");
    TextureManager::getInstance() -> Load("src/resources/Samurai/Attack_2.png", "player_Attack2");
    TextureManager::getInstance() -> Load("src/resources/Samurai/Attack_3.png", "player_Attack3");
    TextureManager::getInstance() -> Load("src/resources/Samurai/Jump.png", "player_Jump");
    TextureManager::getInstance() -> Load("src/resources/Samurai/Protection.png", "player_Protect");
    
   
    player = new Samurai(new Properties("player_Idle", 128, 128, 100, 300));
     
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
    float dt = Timer::getInstance() -> getDeltaTime();
    player -> Update(dt);
}
void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 203, 195, 227, 255);
    SDL_RenderClear(m_Renderer);
    
    player ->Draw();
    SDL_RenderPresent(m_Renderer);
}
void Engine::Events(){
    Input::getInstance() -> Listen();
}
