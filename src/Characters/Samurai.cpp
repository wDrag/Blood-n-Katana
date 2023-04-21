#include "Characters/Samurai.h"
#include "Camera/Camera.h"

#include <SDL2/SDL.h>

#define right 1
#define left -1
#define up   -1
#define down  1

Samurai::Samurai(Properties* props) : Character(props){
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider;
    m_Collider -> SetBuffer(0, 0, 0, 0);
 
    m_RigidBody = new RigidBody();
    m_RigidBody -> setGravity(5.0f);
    
    m_FaceDir = 1;
    
    Input::getInstance() -> UnlockKey();
    
    m_Animation = new AnimationHandler();
    Idling();
}

void Samurai::Draw(){
    m_Animation -> Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    // Vector2D cam = Camera::GetInstance() -> GetPosition();
    // SDL_Rect box = m_Collider -> GetBox();
    // box.x -= cam.X;
    // box.y -= cam.Y;
    // SDL_RenderDrawRect(Engine::GetInstance() -> getRenderer(), &box);
}

void Samurai::WalkLeft(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_Jumpable) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_Jumpable)
        m_FaceDir = 0;
    m_RigidBody -> ApplyForceX(3 * left);
    m_Animation -> SetProps("player_Walk", 1, 9, 125, m_Dir[m_FaceDir]);
}

void Samurai::WalkRight(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_Jumpable) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_Jumpable)
        m_FaceDir = 1;
    m_RigidBody -> ApplyForceX(3 * right);
    m_Animation -> SetProps("player_Walk", 1, 9, 125, m_Dir[m_FaceDir]);
}

void Samurai::RunLeft(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_Jumpable) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_Jumpable)
        m_FaceDir = 0;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(7 * left);
    m_Animation -> SetProps("player_Run", 1, 8, 125, m_Dir[m_FaceDir]);
}

void Samurai::RunRight(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_Jumpable) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_Jumpable)
        m_FaceDir = 1;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(7 * right);
    m_Animation -> SetProps("player_Run", 1, 8, 125, m_Dir[m_FaceDir]);
}

void Samurai::Jump(float dt){
    if (m_Jumpable){
        m_Animation -> AnimationStart();
        m_IsJumping = true;
        m_Jumpable = false;
        m_RigidBody -> ApplyForceY(up * m_JumpForce);
    }
    if (m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody -> ApplyForceY(up * m_JumpForce);
    }
    else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
        m_RigidBody -> UnsetForce();
    }
    if (m_IsJumping || !m_Jumpable){
        m_Animation -> SetProps("player_Jump", 1, 2, 100, m_Dir[m_FaceDir]);
    }
}

void Samurai::Idling(){
    m_RigidBody -> UnsetForce();
    m_Animation -> SetProps("player_Idle", 1, 6, 150, m_Dir[m_FaceDir]);
}


void Samurai::Update(float dt){

    if (Input::getInstance() -> NoKeyDown()){
        Idling();
    }

    //move


    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_A)){
        // WalkLeft();
        RunLeft();
    }
    
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_D)){
        RunRight();
        // WalkRight();
    }
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_W)){
        Jump(dt);
    }

    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_A) && Input::getInstance() -> GetKeyDown(SDL_SCANCODE_D)){
        Idling();
    }
    
    // if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_S)){
    //     Protect();
    // }
    
    
    //attack
    // if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_J)){
    //     Attack1();
    // }

    // if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_K)){
    //     Attack2();
    // }

    // if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_L)){
    //     Attack3();
    // }
    m_RigidBody -> Update(dt);

    //collision handling
    //X axis
    m_LastSafePosition.X = m_Transform -> X;
    m_Transform -> X += m_RigidBody -> Position().X;
    m_Collider -> SetBox(m_Transform -> X + 43, m_Transform -> Y + 48, 43, 80);

    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }

    //Y axis
    m_RigidBody -> Update(dt);
    m_LastSafePosition.Y = m_Transform -> Y;
    m_Transform -> Y += m_RigidBody -> Position().Y;
    m_Collider -> SetBox(m_Transform -> X + 43, m_Transform -> Y + 48, 43, 80);

    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
        m_Jumpable = true;
        m_Transform -> Y = m_LastSafePosition.Y;
    }
    else 
        m_Jumpable = false;
    
    m_Origin -> X = m_Transform -> X + m_Width/2;
    m_Origin -> Y = m_Transform -> Y + m_Height/2;

    m_Animation -> Update(dt);
}

void Samurai::Clean(){
    TextureManager::GetInstance() -> Clean();
}