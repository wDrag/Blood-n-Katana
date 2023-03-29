#include "Characters/Samurai.h"
#include "Graphics/TextureManager.h"
#include "Physics/RigidBody.h"
#include "Inputs/Input.h"

#include <SDL2/SDL.h>

#define right 1
#define left -1
#define up   -1
#define down  1


SDL_RendererFlip m_Dir[2] = {SDL_FLIP_HORIZONTAL, SDL_FLIP_NONE};

Samurai::Samurai(Properties* props) : Character(props){
    m_RigidBody = new RigidBody();
    m_Animation = new AnimationHandler();
}

void Samurai::Draw(){
    m_Animation -> Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Samurai::WalkLeft(){
    m_FaceDir = 0;
    m_State = "Walking";
    m_Animation -> SetProps("player_Walk", 1, 9, 100, m_Dir[m_FaceDir]);
    m_Animation -> AnimationStart();
    // m_RigidBody -> UnsetForce();
    m_RigidBody -> ApplyForceX(4 * left);
}

void Samurai::WalkRight(){
    m_FaceDir = 1;
    m_State = "Walking";
    m_Animation -> SetProps("player_Walk", 1, 9, 100, m_Dir[m_FaceDir]);
    m_Animation -> AnimationStart();
    // m_RigidBody -> UnsetForce();
    m_RigidBody -> ApplyForceX(4 * right);
}

void Samurai::Jump(){
    m_State = "Jumping";
    m_Animation -> SetProps("player_Jump", 1, 9, 100, m_Dir[m_FaceDir]);
    m_Animation -> AnimationStart();
    m_RigidBody -> ApplyForceY(15 * up);
}

void Samurai::Protect(){
    m_State = "Protecting";
    m_Animation -> SetProps("player_Protect", 1, 2, 400, m_Dir[m_FaceDir]);
    m_Animation -> AnimationStart();
    m_RigidBody -> UnsetForce();
}

void Samurai::Idling(){
    m_State = "Idling";
    m_Animation -> SetProps("player_Idle", 1, 6, 100, m_Dir[m_FaceDir]);
    m_Animation -> AnimationStart();
    m_RigidBody -> UnsetForce();
}

void Samurai::Attack1(){
    m_State = "Attacking";
    m_Animation -> SetProps("player_Attack1", 1, 4, 100, m_Dir[m_FaceDir]);
    m_Animation -> AnimationStart();
    m_RigidBody -> UnsetForce();
}

void Samurai::Attack2(){
    m_State = "Attacking";
    m_Animation -> SetProps("player_Attack2", 1, 5, 100, m_Dir[m_FaceDir]);
    m_Animation -> AnimationStart();
    m_RigidBody -> UnsetForce();
}

void Samurai::Attack3(){
    m_State = "Attacking";
    m_Animation -> SetProps("player_Attack3", 1, 4, 100, m_Dir[m_FaceDir]);
    m_Animation -> AnimationStart();
    m_RigidBody -> UnsetForce();
}

void Samurai::Update(float dt){


    //move

    Idling();

    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_LEFT)){
        WalkLeft();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_A)){
        WalkLeft();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_RIGHT)){
        WalkRight();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_D)){
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
    TextureManager::getInstance() -> Clean();
}