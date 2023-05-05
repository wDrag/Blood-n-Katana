#include "Characters/Boss_Vampire.h"
#include "Camera/Camera.h"
#include <SDL2/SDL.h>

#define right 1
#define left -1
#define up   -1
#define down  1

Countesses* Countesses::s_Instance = nullptr;

Countess_Vampire::Countess_Vampire(Properties* props) : Character(props){

    m_JumpTime = Globals::GetInstance() -> JUMP_TIME * 1.5f;
    m_JumpForce = Globals::GetInstance() -> JUMP_FORCE;

    m_Collider = new Collider;
    m_Collider -> SetBuffer(0, 0, 0, 0);
 
    m_RigidBody = new RigidBody();
    m_RigidBody -> setGravity(5.0f);
    
    m_FaceDir = 1;

    m_isAlive = true;
    
    m_Animation = new AnimationHandler();
    Idling();
}

void Countess_Vampire::Draw(){
    m_Animation -> Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Dir[m_FaceDir]);

    // Vector2D cam = Camera::GetInstance() -> GetPosition();
    // SDL_Rect box = m_Collider -> GetBox();
    // box.x -= cam.X;
    // box.y -= cam.Y;
    // SDL_RenderDrawRect(Engine::GetInstance() -> getRenderer(), &box);
}

void Countess_Vampire::RunLeft(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_isGrounded)
        m_FaceDir = 0;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(10 * left);
    if (m_isRunning == false)
        m_Animation -> AnimationStart();
    m_isRunning = true;
    m_Animation -> SetProps("Countess_Run", 1, 6, 125);
}

void Countess_Vampire::RunRight(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_isGrounded)
        m_FaceDir = 1;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(10 * right);
    if (m_isRunning == false)
        m_Animation -> AnimationStart();
    m_isRunning = true;
    m_Animation -> SetProps("Countess_Run", 1, 6, 125);
}

void Countess_Vampire::Jump(float dt){
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
        m_JumpTime = Globals::GetInstance() -> JUMP_TIME;
        m_RigidBody -> UnsetForce();
    }
    if (m_isJumping || !m_isGrounded){
        m_Animation -> SetProps("Countess_Jump", 1, 2, 100);
    }
}

void Countess_Vampire::Idling(){
    m_isRunning = false;
    // m_isAttacking1 = false;
    // m_isAttacking2 = false;
    // m_isAttacking3 = false;
    m_RigidBody -> UnsetForce();
    m_Animation -> SetProps("Countess_Idle", 1, 5, 150);
}

/// actions and attack

void Countess_Vampire::Attack1(){
    if (m_isAttacking1 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking1 == false)
        m_Animation -> AnimationStart();
    m_isAttacking1 = true;
    m_Animation -> SetProps("Countess_Attack1", 1, 8, 150);
}
void Countess_Vampire::Attack2(){
    if (m_isAttacking2 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking2 == false)
        m_Animation -> AnimationStart();
    m_isAttacking2 = true;
    m_Animation -> SetProps("Countess_Attack2", 1, 7, 150);
}
void Countess_Vampire::Attack3(){
    if (m_isAttacking3 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking3 == false)
        m_Animation -> AnimationStart();
    m_isAttacking3 = true;
    m_Animation -> SetProps("Countess_Attack3", 1, 10, 150);   
}

void Countess_Vampire::Die(){
    m_RigidBody -> UnsetForce();
    if (m_isDying == false)
        m_Animation -> AnimationStart();
    m_isDying = true;
    m_Animation -> SetProps("Skeleton_Dead", 1, 8, 200);
}


void Countess_Vampire::Update(float dt){


    // SDL_Log("die here? X: %f Y: %f", m_Transform -> X, m_Transform -> Y);
    // SDL_Log("Force X: %f Y: %f", m_RigidBody ->Force().X, m_RigidBody->Force().Y);
    // SDL_Log("Acceleration X: %f Y: %f", m_RigidBody ->Acceleration().X, m_RigidBody->Acceleration().Y);
    // SDL_Log("Velocity X: %f Y: %f", m_RigidBody ->Velocity().X, m_RigidBody->Velocity().Y);
    // SDL_Log("Rigid Body X: %f Y: %f", m_RigidBody ->Position().X, m_RigidBody->Position().Y);
    
    m_RigidBody -> UnsetForce();

    if (m_HP <= 0){
        Die();
    }
    if (m_isDying == true){
        Die();
    }
    if (m_Animation -> ACycle() && m_isDying == true){
        m_isDying = false;
        m_isAlive = false;
        return;
    }

    if (!m_isDying){

    if (m_Animation -> ACycle() && isAttacking() == true){
        stopAttack();
    }

    //move

    Idling();
    
    //move
    
    //attack

    if (m_isAttacking1 == true){
        Attack1();
    }
    if (m_isAttacking2 == true){
        Attack2();
    }
    if (m_isAttacking3 == true){
        Attack3();
    }

    if (m_RigidBody -> Velocity().Y > 0 && !m_isGrounded){
        m_isFalling = true;
        m_Animation -> SetProps("Countess_Fall", 1, 2, 100);
    }
    else m_isFalling = false;

    }

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

void Countess_Vampire::Clean(){
    TextureManager::GetInstance() -> Clean();
}