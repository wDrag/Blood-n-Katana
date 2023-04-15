#include "Core/engine.h"
#include "Graphics/TextureManager.h"
#include "Physics/Transform.h"
#include "Characters/Samurai.h"
#include "Inputs/Input.h"
#include "Timer/Timer.h"
#include "Map/MapParser.h"

Engine* Engine::s_Instance = nullptr;
Samurai* player = nullptr;
GameMap* m_LevelMap = nullptr;

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
    
    if (!MapParser::GetInstance() -> Load()){
        SDL_Log("Failed to load map");
        return false;
    }
    m_LevelMap = MapParser::GetInstance() -> GetMap("MAP");
    TextureManager::GetInstance() -> Load("player_Idle", "src/resources/Samurai/Idle.png");
    TextureManager::GetInstance() -> Load("player_Walk", "src/resources/Samurai/Walk.png");
    TextureManager::GetInstance() -> Load("player_Run", "src/resources/Samurai/Run.png");
    TextureManager::GetInstance() -> Load("player_Attack1", "src/resources/Samurai/Attack_1.png");
    TextureManager::GetInstance() -> Load("player_Attack2", "src/resources/Samurai/Attack_2.png");
    TextureManager::GetInstance() -> Load("player_Attack3", "src/resources/Samurai/Attack_3.png");
    TextureManager::GetInstance() -> Load("player_Jump", "src/resources/Samurai/Jump.png");
    TextureManager::GetInstance() -> Load("player_Protect", "src/resources/Samurai/Protection.png");
    
   
    player = new Samurai(new Properties("player_Idle", 128, 128, 100, 300));

    return m_isRunning = true;
}

void Engine::Clean(){
    MapParser::GetInstance() -> Clean();
    TextureManager::GetInstance() -> Clean();
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
    m_LevelMap -> Update();
    player -> Update(dt);
}
void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 203, 195, 227, 255);
    SDL_RenderClear(m_Renderer);

    m_LevelMap -> Render();    
    player ->Draw();
    SDL_RenderPresent(m_Renderer);
}
void Engine::Events(){
    Input::getInstance() -> Listen();
}
