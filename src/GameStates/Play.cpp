#include "GameStates/Play.h"
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
#include "Globals/Globals.h"
#include "GameStates/Victory.h"
#include "GameStates/GameOver.h"
#include "Fonts/FontsManager.h"
#include <random>
#include <ctime>
#include <string>

Play::Play(){
    m_Pause = false;
    m_isDefeated = false;
}

void Play::Init(){
    Countesses::GetInstance() -> Clean();
    BloodChargesManager::GetInstance() -> Clean();
    Skeletons::GetInstance() -> Clean();
    Players::GetInstance() -> Clean();
    Players::GetInstance() -> Spawn("Player_Idle", Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> StartingX, Globals::GetInstance() -> StartingY);
    Camera::GetInstance() -> setTarget(Players::GetInstance() ->GetPlayer(0) -> GetOrigin());
    Input::getInstance() -> UnlockKey();
    numSkeletonsKilled = 0;
    numSkeletonSpawned = 0;
    numBoss = 0;
    B_Pause = new Button(10, 10, "B_Pause");
    m_isVictory = false;
    m_isDefeated = false;
    m_Pause = false;
}

void Play::Update(float dt){
    B_Pause -> Update();
    Events();

    if (!m_Pause && !m_isDefeated && !m_isVictory){
        numSkeletonsKilled = numSkeletonSpawned - Skeletons::GetInstance() -> GetSkeletonsNum();
        if (numSkeletonsKilled >= 4 && numBoss == 0){
            Countesses::GetInstance() -> Spawn("Countess_Idle", Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> StartingXB, Globals::GetInstance() -> StartingYB);
            numBoss++;
        }
        int rnd = Globals ::GetInstance() -> Random(1, 500);
        if (rnd == 123||Skeletons::GetInstance() -> GetSkeletonsNum() == 0){
            int spwnX = Globals::GetInstance() -> Random(100, 2600);
            if (numBoss > 0)
                spwnX = Globals::GetInstance() -> Random(-400, 400) + Countesses::GetInstance() -> GetCountess(0) -> GetOrigin() -> X;
            int spwnY = 250;
            Skeletons::GetInstance() -> Spawn("Skeleton_Idle", Globals::GetInstance() -> HumanoidFrameSize, Globals::GetInstance() -> HumanoidFrameSize, spwnX, spwnY);
            numSkeletonSpawned++;
        }

        Players::GetInstance() -> Update(dt);
        Camera::GetInstance() ->Update(dt);
        Skeletons::GetInstance() -> Update(dt);
        Countesses::GetInstance() -> Update(dt);
        BloodChargesManager::GetInstance() -> Update(dt);
        if (Players::GetInstance() -> GetPlayersNum() == 0)
            m_isDefeated = true;
        if (Countesses::GetInstance() -> GetCountessesNum() == 0 && numBoss > 0 && numSkeletonsKilled >= 10)
            m_isVictory = true;
    }
    if (m_isDefeated){
        m_isDefeated = false;
        toGameOver();
        return;
    }
    if (m_isVictory){
        m_isVictory = false;
        toVictory();
        return;
    }

}

void Play::Render(){
    Engine::GetInstance() -> GetMap() -> Render();
    FontsManager::GetInstance() -> Draw("BreatheFireSmol", "Kill the Countess and 10 Skeletons to win!", 40, 800, {255, 250, 250, 255});
    std::string str = "Skeletons killed: " + std::to_string(numSkeletonsKilled) + "/10";
    FontsManager::GetInstance() -> Draw("BreatheFireSmol", str, 1000, 800, {255, 250, 250, 255});
    Players::GetInstance() -> Draw();
    Countesses::GetInstance() -> Draw();
    Skeletons::GetInstance() -> Draw();
    BloodChargesManager::GetInstance() -> Draw();
    B_Pause -> Draw();
}

void Play::Quit(){
    Countesses::GetInstance() -> Clean();
    BloodChargesManager::GetInstance() -> Clean();
    Skeletons::GetInstance() -> Clean();
    Players::GetInstance() -> Clean();
}

void Play::Events(){

    
    if (!m_Pause && B_Pause -> GetState() == CLICKED){
        m_Pause = true;
        Pause();
        SDL_Delay(200);
        return;
    }
    if (m_Pause && B_Pause -> GetState() == CLICKED){
        m_Pause = false;
        Continue();
        SDL_Delay(200);
        return;
    }
}

void Play::Pause(){
    B_Pause -> ChangeTexture("B_Play");
    Input::getInstance() -> LockKey();
}

void Play::Continue(){
    B_Pause -> ChangeTexture("B_Pause");
    Input::getInstance() -> UnlockKey();
}

void Play::toGameOver(){
    Engine::GetInstance() -> ChangeState(new GameOver());
}
void Play::toVictory(){
    Engine::GetInstance() -> ChangeState(new Victory());
}