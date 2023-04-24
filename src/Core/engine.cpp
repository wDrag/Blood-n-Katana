#include "Core/engine.h"
#include "Graphics/TextureManager.h"
#include "Physics/Transform.h"
#include "Characters/Samurai.h"
#include "Inputs/Input.h"
#include "Timer/Timer.h"
#include "Map/MapParser.h"
#include "Camera/Camera.h"

Engine* Engine::s_Instance = nullptr;
Samurai* player = nullptr;


bool Engine::Init(){
    if (SDL_Init(SDL_INIT_VIDEO)!= 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags WINFLAGS = (SDL_WindowFlags)(SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("BND", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, WINFLAGS);
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

    player = new Samurai(new Properties("player_Idle", 128, 128, 200, 450));

    Camera::GetInstance() -> setTarget(player -> GetOrigin());

    // TextureManager::GetInstance() -> checkMap();

    return m_isRunning = true;
}

void Engine::Clean(){
    MapParser::GetInstance() -> Clean();
    TextureManager::GetInstance() -> Clean();
    player -> Clean();
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
    Camera::GetInstance() -> Update(dt);
    player -> Update(dt);
}
void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 8, 14, 33, 1);
    SDL_RenderClear(m_Renderer);

    m_LevelMap -> Render();    
    player -> Draw();
    SDL_RenderPresent(m_Renderer);
}
void Engine::Events(){
    Input::getInstance() -> Listen();
}
