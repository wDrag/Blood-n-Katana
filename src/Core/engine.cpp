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
#include "GameStates/GameOver.h"
#include "GameStates/Victory.h"
#include "GameStates/Play.h"
#include "GameStates/Home.h"
#include "Fonts/FontsManager.h"
#include <random>
#include <ctime>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init(){

    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!= 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1){
        SDL_Log("Failed to initialize TTF: %s", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        SDL_Log("Mixer Error: %s", Mix_GetError());
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
    m_Music = Mix_LoadMUS("src/resources/Music/Gokuraku Joudo.mp3");
    if (m_Music == NULL){
        SDL_Log("Failed to load Music: %s", Mix_GetError());
        return false;
    }
    m_LevelMap = MapParser::GetInstance() -> GetMap("MAP"); 

    FontsManager::GetInstance() -> Load("src/resources/Fonts/Bloodthirsty-3j0p.ttf", "Bloodthirsty", 200);
    FontsManager::GetInstance() -> Load("src/resources/Fonts/BreatheFireIi-2z9W.ttf", "BreatheFire", 150);
    FontsManager::GetInstance() -> Load("src/resources/Fonts/BreatheFireIi-2z9W.ttf", "BreatheFireSmol", 50);
    FontsManager::GetInstance() -> Load("src/resources/Fonts/KatanaRegular-X3jXP.ttf", "Katana", 200);

    TextureManager::GetInstance() -> ParseTextures("src/resources/Textures.xml", "Button");
    TextureManager::GetInstance() -> ParseTextures("src/resources/Textures.xml", "Samurai");
    TextureManager::GetInstance() -> ParseTextures("src/resources/Textures.xml", "Countess");
    TextureManager::GetInstance() -> ParseTextures("src/resources/Textures.xml", "Skeleton");
    TextureManager::GetInstance() -> ParseTextures("src/resources/Textures.xml", "Other");
    
    CM::GetInstance() -> StatsParser("src/Characters/GameStats.xml", "Samurai");
    CM::GetInstance() -> StatsParser("src/Characters/GameStats.xml", "Countess");
    CM::GetInstance() -> StatsParser("src/Characters/GameStats.xml", "Skeleton");

    
    curState = -1;
    m_GameStates.clear();

    B_Mute = new Button(Globals::GetInstance() -> SCREEN_WIDTH - 110, 10, "B_Sound");
    m_isMuted = false;
    Mix_PlayMusic(m_Music, -1);
    Mix_VolumeMusic(80);

    PushState(new Home());

    m_GameStates[curState] -> Init();
    m_GameStates[curState] -> Render();


    return m_isRunning = true;
}


void Engine::Clean(){
    MapParser::GetInstance() -> Clean();
    TextureManager::GetInstance() -> Clean();
    Players::GetInstance() -> Clean();
    Countesses::GetInstance() -> Clean();
    Skeletons::GetInstance() -> Clean();
    BloodChargesManager::GetInstance() -> Clean();
    CM::GetInstance() -> StatsClean();
    Quit();
}

void Engine::Quit(){
    // for(int i = 0; i < m_GameStates.size(); i++){
    //     m_GameStates[i] -> Quit();
    // }
    m_GameStates.clear();
    curState = -1;
    m_isRunning = false;
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}


void Engine::Update(){
    float dt = Timer::getInstance() -> getDeltaTime();
    m_GameStates[curState] -> Update(dt);
    B_Mute -> Update();
    if (!m_isMuted && B_Mute -> GetState() == CLICKED){
        m_isMuted = true;
        B_Mute -> ChangeTexture("B_Sound_Off");
        Mix_PauseMusic();
        SDL_Delay(200);
    }
    else if (m_isMuted && B_Mute -> GetState() == CLICKED){
        m_isMuted = false;
        B_Mute -> ChangeTexture("B_Sound");
        Mix_ResumeMusic();
        SDL_Delay(200);
    }
}
void Engine::Render(){
    SDL_RenderClear(m_Renderer);
    m_GameStates[curState] -> Render();
    B_Mute -> Draw();
    SDL_RenderPresent(m_Renderer);
}
void Engine::Events(){
    Input::getInstance() -> Listen();
}
void Engine::ChangeState(GameState* state){
    PushState(state);
    m_GameStates[curState] -> Init();
}

void Engine::PopState()
{
    m_GameStates.erase(m_GameStates.begin() + curState);
    curState--;
}
void Engine::PushState(GameState* state)
{
    curState++; 
    m_GameStates.push_back(state);
}