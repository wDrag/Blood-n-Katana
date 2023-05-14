#include "Characters/Skeleton.h"
#include "Camera/Camera.h"
#include <SDL2/SDL.h>
#include <cmath>

#define right 1
#define left -1
#define up   -1
#define down  1

Skeletons* Skeletons::s_Instance = nullptr;


Skeleton::Skeleton(Properties* props) : Character(props){

    m_JumpTime = Globals::GetInstance() -> JUMP_TIME * 1.5f;
    m_JumpForce = Globals::GetInstance() -> JUMP_FORCE;

    m_Collider = new Collider;
    m_Collider -> SetBuffer(0, 0, 0, 0);
 
    m_RigidBody = new RigidBody();
    m_RigidBody -> setGravity(5.0f);
    
    m_FaceDir = 0;
    
    m_isAlive = true;

    int m_HP = CM::GetInstance()->GetStats("Skeleton").HP;

    m_HP_Bar_MAX = {(int)m_Transform -> X + 15, (int)m_Transform -> Y + 30, 96, 8};
    m_HP_Bar = m_HP_Bar_MAX;


    m_Animation = new AnimationHandler();
    Idling();
}

void Skeleton::Draw(){
    SDL_SetRenderDrawColor(Engine::GetInstance() -> getRenderer(), 77, 21, 38, 255);
    SDL_RenderFillRect(Engine::GetInstance() -> getRenderer(), &m_HP_Bar_MAX);
    SDL_SetRenderDrawColor(Engine::GetInstance() -> getRenderer(), 255, 206, 0, 255);
    SDL_RenderFillRect(Engine::GetInstance() -> getRenderer(), &m_HP_Bar);

    m_Animation -> Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Dir[m_FaceDir]);

    // Vector2D cam = Camera::GetInstance() -> GetPosition();
    // SDL_Rect box = m_Collider -> GetBox();
    // box.x -= cam.X;
    // box.y -= cam.Y;
    // SDL_RenderDrawRect(Engine::GetInstance() -> getRenderer(), &box);
}

void Skeleton::RunLeft(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_isGrounded)
        m_FaceDir = 0;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(3 * left);
    if (m_isRunning == false)
        m_Animation -> AnimationStart();
    m_isRunning = true;
    m_Animation -> SetProps("Skeleton_Run", 1, 8, 125);
}

void Skeleton::RunRight(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_isGrounded)
        m_FaceDir = 1;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(3 * right);
    if (m_isRunning == false)
        m_Animation -> AnimationStart();
    m_isRunning = true;
    m_Animation -> SetProps("Skeleton_Run", 1, 8, 125);
}

void Skeleton::Jump(float dt){
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
        m_Animation -> SetProps("Skeleton_Jump", 1, 2, 100);
    }
}

void Skeleton::Idling(){
    m_isRunning = false;
    // m_isAttacking1 = false;
    // m_isAttacking2 = false;
    // m_isAttacking3 = false;
    m_RigidBody -> UnsetForce();
    m_Animation -> SetProps("Skeleton_Idle", 1, 7, 100);
}

/// actions and attack

void Skeleton::Attack1(){
    if (m_isAttacking1 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking1 == false)
        m_Animation -> AnimationStart();
    m_isAttacking1 = true;
    m_Animation -> SetProps("Skeleton_Attack1", 1, 4, 250);
}
void Skeleton::Attack2(){
    if (m_isAttacking2 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking2 == false)
        m_Animation -> AnimationStart();
    m_isAttacking2 = true;
    m_Animation -> SetProps("Skeleton_Attack2", 1, 6, 250);
}
void Skeleton::Attack3(){
    if (m_isAttacking3 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking3 == false)
        m_Animation -> AnimationStart();
    m_isAttacking3 = true;
    m_Animation -> SetProps("Skeleton_Attack3", 1, 4, 250);   
}

void Skeleton::Die(){
    m_RigidBody -> UnsetForce();
    if (m_isDying == false)
        m_Animation -> AnimationStart();
    m_isDying = true;
    m_Animation -> SetProps("Skeleton_Dead", 1, 8, 200);
}

void Skeleton::Hurt(){
    m_RigidBody -> UnsetForce();
    if (m_isHurting == false)
        m_Animation -> AnimationStart();
    m_isHurting = true;
    m_Animation -> SetProps("Skeleton_Dead", 1, 2, 50);
}

void Skeleton::Update(float dt){


    // SDL_Log("die here? X: %f Y: %f", m_Transform -> X, m_Transform -> Y);
    // SDL_Log("Force X: %f Y: %f", m_RigidBody ->Force().X, m_RigidBody->Force().Y);
    // SDL_Log("Acceleration X: %f Y: %f", m_RigidBody ->Acceleration().X, m_RigidBody->Acceleration().Y);
    // SDL_Log("Velocity X: %f Y: %f", m_RigidBody ->Velocity().X, m_RigidBody->Velocity().Y);
    // SDL_Log("Rigid Body X: %f Y: %f", m_RigidBody ->Position().X, m_RigidBody->Position().Y);
    
    m_RigidBody -> UnsetForce();

    if (m_HP <= 0){
        m_HP = 0;
        Die();
    }
    if (m_isDying == true){
        Die();
    }
    Vector2D cam = Camera::GetInstance() -> GetPosition();

    m_HP_Bar_MAX = {(int)(m_Transform -> X + 15 - cam.X), (int)(m_Transform -> Y + 30 - cam.Y), 96, 8};
    m_HP_Bar = m_HP_Bar_MAX;
    
    m_HP_Bar.w = m_HP * m_HP_Bar_MAX.w / CM::GetInstance() -> GetStats("Skeleton").HP;
    if (m_Animation -> ACycle() && m_isDying == true){
        m_isDying = false;
        m_isAlive = false;
        return;
    }

    if (!m_isDying){

        if (m_isHurting == true){
            Hurt();
        }
        if (m_Animation -> ACycle() && m_isHurting == true){
            m_isHurting = false;
        }

        if (!m_isHurting == true){
        
            if (m_Animation -> ACycle() && isAttacking() == true){
                stopAttack();
                Players::GetInstance() -> DealDMG();
            }

            //move
            //attack
            int py = Players::GetInstance() -> GetPlayer(0) ->GetOrigin() -> Y;
            if (abs(py - m_Origin -> Y) >= 45){
                Idling();
            }
            else {
                int px = Players::GetInstance() -> GetPlayer(0) ->GetOrigin() -> X;
                if (abs(px - m_Origin -> X) >= 45){
                    if (m_isFalling == true){
                        Idling();
                    }
                    else{
                        if (px > m_Origin -> X){
                            RunRight();
                        }
                        else {
                            RunLeft();
                        }
                    }
                }
                else {     
                    if (m_isFalling == true){
                        Idling();
                    }
                    else{
                        if (px > m_Origin -> X){
                            m_FaceDir = 1;
                        }
                        else {
                            m_FaceDir = 0;
                        }
                        int rnd = Globals::GetInstance() -> Random(1, 120);
                        switch (rnd)
                        {
                        case 1:
                            if (isAttacking() == false)
                                Attack1();
                            break;
                        case 2:
                            if (isAttacking() == false)
                                Attack2();
                            break;
                        case 3:
                            if (isAttacking() == false)
                                Attack3();
                            break;
                        default:
                            Idling();
                            break;
                        }
                    }
                }
            }

            if (m_isAttacking1 == true){
                Attack1();
                SDL_Rect Hitbox = {(int)m_Transform -> X + 100 - (!m_FaceDir) * 100, (int)m_Transform -> Y + 50, 35, 60};
                if (m_Animation -> getFrame() >= 4)
                    Players::GetInstance() -> checkHit(Hitbox, m_ATK * m_AttackMod1);
            }
            if (m_isAttacking2 == true){
                Attack2();
                SDL_Rect Hitbox = {(int)m_Transform -> X + 50 - (!m_FaceDir) * 50, (int)m_Transform -> Y + 50, 70, 50};
                if (m_Animation -> getFrame() >= 4)
                    Players::GetInstance() -> checkHit(Hitbox, m_ATK * m_AttackMod2);
            }
            if (m_isAttacking3 == true){
                Attack3();
                SDL_Rect Hitbox = {(int)m_Transform -> X + 75 - (!m_FaceDir) * 75, (int)m_Transform -> Y + 60, 45, 65};
                if (m_Animation -> getFrame() >= 3)
                    Players::GetInstance() -> checkHit(Hitbox, m_ATK * m_AttackMod3);
            }
        }
        if (m_RigidBody -> Velocity().Y > 0 && !m_isGrounded){
            m_isFalling = true;
        }
        else m_isFalling = false;

    }
    //collision handling
    //X axis
    m_RigidBody -> Update(dt);
    m_LastSafePosition.X = m_Transform -> X;
    m_Transform -> X += m_RigidBody -> Position().X;
    m_Collider -> SetBox(m_Transform -> X + 50, m_Transform -> Y + 70, 30, 60);

    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }
    if (Players::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }
    if (Skeletons::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }
    if (Countesses::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }

    //Y axis
    m_RigidBody -> Update(dt);
    m_LastSafePosition.Y = m_Transform -> Y;
    m_Transform -> Y += m_RigidBody -> Position().Y;
    m_Collider -> SetBox(m_Transform -> X + 50, m_Transform -> Y + 70, 30, 60);
    
    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
        m_isGrounded = true;
        m_Transform -> Y = m_LastSafePosition.Y;
    }
    else 
        m_isGrounded = false;
    if (Players::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_isGrounded = true;
        m_Transform -> Y = m_LastSafePosition.Y;
    }
    if (Skeletons::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_isGrounded = true;
        m_Transform -> Y = m_LastSafePosition.Y;
    }
    if (Countesses::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_isGrounded = true;
        m_Transform -> Y = m_LastSafePosition.Y;
    }

    ///////
    
    m_Origin -> X = m_Transform -> X + m_Width/2;
    m_Origin -> Y = m_Transform -> Y + m_Height/2;

    m_Animation -> Update(dt);
}

void Skeleton::Clean(){
}