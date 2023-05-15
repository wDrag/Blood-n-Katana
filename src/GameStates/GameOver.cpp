#include "GameStates/GameOver.h"
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
#include "GameStates/Play.h"
#include "Fonts/FontsManager.h"
#include "Globals/Globals.h"
#include <random>
#include <ctime>

void GameOver::Init(){
    B_Restart = new Button(Globals::GetInstance() -> SCREEN_WIDTH / 2 - 150, 600, "B_Restart");
    B_Quit = new Button(Globals::GetInstance() -> SCREEN_WIDTH / 2 -50, 600, "B_Quit");
}

void GameOver::Update(float dt){
    B_Restart -> Update();
    B_Quit -> Update();
    Events();   
}

void GameOver::Render(){
    TextureManager::GetInstance() -> DrawButton("YouDied", 0, 0, 1920, 1080, Globals::GetInstance() -> SCREEN_WIDTH, Globals::GetInstance() -> SCREEN_HEIGHT);
    B_Restart -> Draw();
    B_Quit -> Draw();
}

void GameOver::Events(){
    if (B_Restart -> GetState() == CLICKED){
        toPlay();
        SDL_Delay(200);
    }
    if (B_Quit -> GetState() == CLICKED){
        Quit();
        SDL_Delay(200);
    }
}

void GameOver::Quit(){
    Engine::GetInstance() -> Quit();
}

void GameOver::toPlay(){
    Engine::GetInstance() -> ChangeState(new Play());
}

