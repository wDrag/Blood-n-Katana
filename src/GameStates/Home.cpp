#include "GameStates/Home.h"
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

void Home::Init(){
    B_Play = new Button(300, 300, "B_Play");
    B_Quit = new Button(300, 400, "B_Quit");
}

void Home::Update(float dt){
    B_Play -> Update();
    B_Quit -> Update();
    Events();   
}

void Home::Render(){
    TextureManager::GetInstance() -> DrawButton("Background", 0, 0, 512, 384, Globals::GetInstance() -> SCREEN_WIDTH, Globals::GetInstance() -> SCREEN_HEIGHT);

    FontsManager::GetInstance() -> Draw("Bloodthirsty", "Blood", 450, 200, {102, 0, 0, 255});
    FontsManager::GetInstance() -> Draw("BreatheFire", "N", 650, 375, {213, 181, 110, 255});
    FontsManager::GetInstance() -> Draw("Katana", "Katana", 500, 510, {235, 236, 240, 255});
    B_Play -> Draw();
    B_Quit -> Draw();
}

void Home::Events(){
    if (B_Play -> GetState() == CLICKED){
        toPlay();
        SDL_Delay(200);
    }
    if (B_Quit -> GetState() == CLICKED){
        Quit();
        SDL_Delay(200);
    }
}

void Home::Quit(){
    Engine::GetInstance() -> Clean();
}

void Home::toPlay(){
    Engine::GetInstance() -> ChangeState(new Play());
}

