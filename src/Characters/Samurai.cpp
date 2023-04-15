#include "Characters/Samurai.h"
#include "Graphics/TextureManager.h"
#include "Physics/RigidBody.h"
#include "Inputs/Input.h"

#include <SDL2/SDL.h>

#define right 1
#define left -1
#define up   -1
#define down  1

Samurai::Samurai(Properties* props) : Character(props){
    m_RigidBody = new RigidBody();
    m_Animation = new AnimationHandler();
    m_FaceDir = 1;
    Input::getInstance() -> UnlockKey();
    Idling();
}

void Samurai::Draw(){
    m_Animation -> Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Samurai::WalkLeft(){
    // m_Animation -> SetDir(m_Dir[m_FaceDir]);
    if (m_State == "Attacking1" || m_State == "Attacking2" || m_State == "Attacking3"){
        if (!m_Animation -> ACycle())
            return;
    }
    if (m_State != "Walking")
        m_Animation -> AnimationStart();
    m_State = "Walking";
    m_Animation -> SetProps("player_Walk", 1, 9, 125, m_Dir[m_FaceDir]);
    m_RigidBody -> ApplyForceX(3 * left);
    // m_RigidBody -> UnsetForce();
}

void Samurai::WalkRight(){
    // m_Animation -> SetDir(m_Dir[m_FaceDir]);
    if (m_State == "Attacking1" || m_State == "Attacking2" || m_State == "Attacking3"){
        if (!m_Animation -> ACycle())
            return;
    }
    if (m_State != "Walking")
        m_Animation -> AnimationStart();
    m_State = "Walking";
    m_Animation -> SetProps("player_Walk", 1, 9, 125, m_Dir[m_FaceDir]);
    m_RigidBody -> ApplyForceX(3 * right);
    // m_RigidBody -> UnsetForce();
}

void Samurai::Jump(){
    if (m_State == "Attacking1" || m_State == "Attacking2" || m_State == "Attacking3"){
        if (!m_Animation -> ACycle())
            return;
    }
    if (m_State != "Jumping")
        m_Animation -> AnimationStart();
    m_State = "Jumping";
    m_Animation -> SetProps("player_Jump", 1, 9, 100, m_Dir[m_FaceDir]);
    // m_RigidBody -> UnsetForce();
    m_RigidBody -> ApplyForceY(7 * up);
}

void Samurai::Protect(){
    m_RigidBody -> UnsetForce();
    if (m_State == "Attacking1" || m_State == "Attacking2" || m_State == "Attacking3"){
        if (!m_Animation -> ACycle())
            return;
    }
    if (m_State != "Protecting")
        m_Animation -> AnimationStart();
    m_State = "Protecting";
    m_Animation -> SetProps("player_Protect", 1, 2, 400, m_Dir[m_FaceDir]);
}

void Samurai::Idling(){
    m_RigidBody -> UnsetForce();
    if (m_State == "Attacking1" || m_State == "Attacking2" || m_State == "Attacking3"){
        if (!m_Animation -> ACycle())
            return;
        else Input :: getInstance() -> UnlockKey();
    }
    if (m_State != "Idling")
        m_Animation -> AnimationStart();
    m_State = "Idling";
    m_Animation -> SetProps("player_Idle", 1, 6, 150, m_Dir[m_FaceDir]);
}

void Samurai::Attack1(){
    m_RigidBody -> UnsetForce();
    if (m_State != "Attacking1"){
        Input::getInstance() -> LockKey();
        m_Animation -> AnimationStart();
    }
    m_State = "Attacking1";
    m_Animation -> SetProps("player_Attack1", 1, 4, 180, m_Dir[m_FaceDir]);
}

void Samurai::Attack2(){
    m_RigidBody -> UnsetForce();
    if (m_State != "Attacking2"){
        Input::getInstance() -> LockKey();
        m_Animation -> AnimationStart();
    }
    m_State = "Attacking2";
    m_Animation -> SetProps("player_Attack2", 1, 5, 210, m_Dir[m_FaceDir]);
}

void Samurai::Attack3(){
    m_RigidBody -> UnsetForce();
    if (m_State != "Attacking3"){
        Input::getInstance() -> LockKey();
        m_Animation -> AnimationStart();
    }
    m_State = "Attacking3";
    m_Animation -> SetProps("player_Attack3", 1, 4, 180, m_Dir[m_FaceDir]);
}

void Samurai::Update(float dt){
    if (m_State == "Attacking1" || m_State == "Attacking2" || m_State == "Attacking3"){
        if (m_Animation -> OverCycle()){
            Input::getInstance() -> UnlockKey();
        }    
    }
    //move
    if (Input::getInstance() -> NoKeyDown()){
        Idling();
    }
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_LEFT)){
        m_FaceDir = 0;
        WalkLeft();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_A)){
        m_FaceDir = 0;
        WalkLeft();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_RIGHT)){
        m_FaceDir = 1;
        WalkRight();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_D)){
        m_FaceDir = 1;
        WalkRight();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_W)){
        Jump();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_UP)){
        Jump();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_S)){
        Protect();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_DOWN)){
        Protect();
    }

    //attack
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_J)){
        Attack1();
    }

    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_K)){
        Attack2();
    }

    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_L)){
        Attack3();
    }

    m_RigidBody -> Update(dt);
    m_Transform -> TranslateX(m_RigidBody -> Position().X);
    // m_RigidBody -> setGravity(0);
    // m_Transform -> TranslateY(m_RigidBody -> Position().Y);
    m_Animation -> Update(dt);
}

void Samurai::Clean(){
    TextureManager::GetInstance() -> Clean();
}