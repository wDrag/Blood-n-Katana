#include "Characters/Samurai.h"
#include "Camera/Camera.h"

#include <SDL2/SDL.h>

#define right 1
#define left -1
#define up   -1
#define down  1

Samurai::Samurai(Properties* props) : Character(props){

    m_isFalling = false;
    m_isRunning = false;
    m_isAttacking1 = false;
    m_isAttacking2 = false;
    m_isAttacking3 = false;
    m_isJumping = false;
    m_isProtecting = false;
    m_isGrounded = false;

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
    m_Animation -> Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Dir[m_FaceDir]);

    // Vector2D cam = Camera::GetInstance() -> GetPosition();
    // SDL_Rect box = m_Collider -> GetBox();
    // box.x -= cam.X;
    // box.y -= cam.Y;
    // SDL_RenderDrawRect(Engine::GetInstance() -> getRenderer(), &box);
}

//no need to walk

// void Samurai::WalkLeft(){
//     if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
//         m_RigidBody -> UnsetForce();
//         return;
//     }
//     if (m_isGrounded)
//         m_FaceDir = 0;
//     m_RigidBody -> ApplyForceX(3 * left);
//     m_Animation -> SetProps("player_Walk", 1, 9, 125);
// }

// void Samurai::WalkRight(){
//     if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
//         m_RigidBody -> UnsetForce();
//         return;
//     }
//     if (m_isGrounded)
//         m_FaceDir = 1;
//     m_RigidBody -> ApplyForceX(3 * right);
//     m_Animation -> SetProps("player_Walk", 1, 9, 125);
// }

void Samurai::RunLeft(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_isGrounded)
        m_FaceDir = 0;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(7 * left);
    m_isRunning = true;
    m_Animation -> SetProps("player_Run", 1, 8, 125);
}

void Samurai::RunRight(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_isGrounded)
        m_FaceDir = 1;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(7 * right);
    m_isRunning = true;
    m_Animation -> SetProps("player_Run", 1, 8, 125);
}

void Samurai::Jump(float dt){
    if (m_isGrounded){
        m_Animation -> AnimationStart();
        m_isJumping = true;
        m_isGrounded = false;
        m_RigidBody -> ApplyForceY(up * m_JumpForce);
    }
    if (m_isJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody -> ApplyForceY(up * m_JumpForce);
    }
    else{
        m_isJumping = false;
        m_JumpTime = JUMP_TIME;
        m_RigidBody -> UnsetForce();
    }
    if (m_isJumping || !m_isGrounded){
        m_Animation -> SetProps("player_Jump", 1, 2, 100);
    }
}

void Samurai::Idling(){
    m_isRunning = false;
    m_isProtecting = false;
    m_isAttacking1 = false;
    m_isAttacking2 = false;
    m_isAttacking3 = false;
    m_RigidBody -> UnsetForce();
    m_Animation -> SetProps("player_Idle", 1, 6, 150);
}

/// actions and attack

void Samurai::Protect(){
    m_RigidBody -> UnsetForce();
    m_isProtecting = true;
    m_Animation -> SetProps("player_Protect", 1, 2, 200);
}

void Samurai::Attack1(){
    m_RigidBody -> UnsetForce();
    m_isAttacking1 = true;
    m_Animation -> SetProps("player_Attack1", 1, 4, 180);
}
void Samurai::Attack2(){
    m_RigidBody -> UnsetForce();
    m_isAttacking2 = true;
    m_Animation -> SetProps("player_Attack2", 1, 5, 220);
}
void Samurai::Attack3(){
    m_RigidBody -> UnsetForce();
    m_isAttacking3 = true;
    m_Animation -> SetProps("player_Attack3", 1, 4, 120);   
}


void Samurai::Update(float dt){

    if (m_isFalling) Input::getInstance() -> LockKey();
    else Input::getInstance() -> UnlockKey();

    if (Input::getInstance() -> NoKeyDown()){
        Idling();
    }

    //move

    if (Input::getInstance() -> GetAxisKey(HORIZONTAL) == right && !isAttacking()){
        RunRight();
    }
    if (Input::getInstance() -> GetAxisKey(HORIZONTAL) == left && !isAttacking()){
        RunLeft();
    }
    if (Input::getInstance() -> GetAxisKey(VERTICAL) == up && !isAttacking()){
        Jump(dt);
    }
    if (Input::getInstance() -> GetAxisKey(VERTICAL) == down && !isAttacking()){
        Protect();
    }
    
    //attack

    if (Input::getInstance() -> GetAttackKey() == 1 && m_isGrounded == true){
        Attack1();
    }
    if (Input::getInstance() -> GetAttackKey() == 2 && m_isGrounded == true){
        Attack2();
    }
    if (Input::getInstance() -> GetAttackKey() == 3 && m_isGrounded == true){
        Attack3();
    }

    if (m_RigidBody -> Velocity().Y > 0 && !m_isGrounded)
        m_isFalling = true;
    else m_isFalling = false;

    //collision handling
    //X axis
    m_RigidBody -> Update(dt);
    m_LastSafePosition.X = m_Transform -> X;
    m_Transform -> X += m_RigidBody -> Position().X;
    m_Collider -> SetBox(m_Transform -> X + 43, m_Transform -> Y + 46, 43, 82);

    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }

    //Y axis
    m_RigidBody -> Update(dt);
    m_LastSafePosition.Y = m_Transform -> Y;
    m_Transform -> Y += m_RigidBody -> Position().Y;
    m_Collider -> SetBox(m_Transform -> X + 43, m_Transform -> Y + 46, 43, 82);
    
    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
        m_isGrounded = true;
        m_Transform -> Y = m_LastSafePosition.Y;
    }
    else 
        m_isGrounded = false;


    ///////
    
    m_Origin -> X = m_Transform -> X + m_Width/2;
    m_Origin -> Y = m_Transform -> Y + m_Height/2;

    m_Animation -> Update(dt);
}

void Samurai::Clean(){
    TextureManager::GetInstance() -> Clean();
}