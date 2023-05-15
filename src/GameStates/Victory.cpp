#include "GameStates/Victory.h"
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

void Victory::Init(){
    B_Restart = new Button(300, 400, "B_Restart");
    B_Quit = new Button(400, 400, "B_Quit");
}

void Victory::Update(float dt){
    B_Restart -> Update();
    B_Quit -> Update();
    Events();   
}

void Victory::Render(){
    TextureManager::GetInstance() -> DrawButton("YouWin", 0, 0, 1280, 720, Globals::GetInstance() -> SCREEN_WIDTH, Globals::GetInstance() -> SCREEN_HEIGHT);
    B_Restart -> Draw();
    B_Quit -> Draw();
}

void Victory::Events(){
    if (B_Restart -> GetState() == CLICKED){
        toPlay();
        SDL_Delay(200);
    }
    if (B_Quit -> GetState() == CLICKED){
        Quit();
        SDL_Delay(200);
    }
}

void Victory::Quit(){
    Engine::GetInstance() -> Quit();
}

void Victory::toPlay(){
    Engine::GetInstance() -> ChangeState(new Play());
}

