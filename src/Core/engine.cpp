#include "Core/engine.h"
#include "Graphics/TextureManager.h"
#include "Physics/Transform.h"
#include "Characters/Chars_Management.h"
#include "Characters/Samurai.h"
#include "Characters/Boss_Vampire.h"
#include "Characters/Skeleton.h"
#include "Inputs/Input.h"
#include "Timer/Timer.h"
#include "Map/MapParser.h"
#include "Camera/Camera.h"
#include "Inputs/Input.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::Init(){
    if (SDL_Init(SDL_INIT_VIDEO)!= 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags WINFLAGS = (SDL_WindowFlags)(SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("BND", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Globals::GetInstance() -> SCREEN_WIDTH, Globals::GetInstance() -> SCREEN_HEIGHT, WINFLAGS);
    if (m_Window == nullptr){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    // SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);

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

    TextureManager::GetInstance() -> ParseTextures("src/resources/Textures.xml", "Samurai");
    TextureManager::GetInstance() -> ParseTextures("src/resources/Textures.xml", "Countess");
    TextureManager::GetInstance() -> ParseTextures("src/resources/Textures.xml", "Skeleton");

    CM::GetInstance() -> StatsParser("src/Characters/GameStats.xml", "Samurai");
    CM::GetInstance() -> StatsParser("src/Characters/GameStats.xml", "Countess");
    CM::GetInstance() -> StatsParser("src/Characters/GameStats.xml", "Skeleton");

    CM::GetInstance() -> checkStats();

    Players::GetInstance() -> Spawn("Player_Idle", Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> StartingX, Globals::GetInstance() -> StartingY);
    Countesses::GetInstance() -> Spawn("Countess_Idle", Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> StartingXB, Globals::GetInstance() -> StartingYB);
    Skeletons::GetInstance() -> Spawn("Skeleton_Idle", Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> StartingX + 50, Globals::GetInstance() -> StartingY - 200);

    Camera::GetInstance() -> setTarget(Players::GetInstance() ->GetPlayer(0) -> GetOrigin());

    // TextureManager::GetInstance() -> checkMap();

    return m_isRunning = true;
}

void Engine::Clean(){
    MapParser::GetInstance() -> Clean();
    TextureManager::GetInstance() -> Clean();
    Players::GetInstance() -> Clean();
    Countesses::GetInstance() -> Clean();
    Skeletons::GetInstance() -> Clean();
    CM::GetInstance() -> StatsClean();
    Quit();
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
    m_LevelMap -> Update();//currently doing nothing
    Players::GetInstance() -> Update(dt);
    Countesses::GetInstance() -> Update(dt);
    Skeletons::GetInstance() -> Update(dt);
    Camera::GetInstance() -> Update(dt);
}
void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 8, 14, 33, 1);
    SDL_RenderClear(m_Renderer);
    m_LevelMap -> Render();    
    Players::GetInstance() -> Draw();
    Countesses::GetInstance() -> Draw();
    Skeletons::GetInstance() -> Draw();
    SDL_RenderPresent(m_Renderer);
}
void Engine::Events(){
    Input::getInstance() -> Listen();
}
