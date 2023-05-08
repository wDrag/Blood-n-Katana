#include "Characters/Samurai.h"
#include "Camera/Camera.h"
#include <SDL2/SDL.h>

#define right 1
#define left -1
#define up   -1
#define down  1

Players* Players::s_Instance = nullptr;

Samurai::Samurai(Properties* props) : Character(props){

    m_JumpTime = Globals::GetInstance() -> JUMP_TIME;
    m_JumpForce = Globals::GetInstance() -> JUMP_FORCE;

    m_Collider = new Collider;
    m_Collider -> SetBuffer(0, 0, 0, 0);
 
    m_RigidBody = new RigidBody();
    m_RigidBody -> setGravity(5.0f);
    
    m_FaceDir = 1;

    m_isAlive = true;
    
    Input::getInstance() -> UnlockKey();

    int m_HP = CM::GetInstance()->GetStats("Samurai").HP;
    
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

void Samurai::RunLeft(){
    if (m_JumpForce < m_RigidBody -> getGravity() && !m_isGrounded) {
        m_RigidBody -> UnsetForce();
        return;
    }
    if (m_isGrounded)
        m_FaceDir = 0;
    m_RigidBody -> ApplyForceY(0);
    m_RigidBody -> ApplyForceX(7 * left);
    if (m_isRunning == false)
        m_Animation -> AnimationStart();
    m_isRunning = true;
    m_Animation -> SetProps("Samurai_Run", 1, 8, 125);
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
    if (m_isRunning == false)
        m_Animation -> AnimationStart();
    m_isRunning = true;
    m_Animation -> SetProps("Samurai_Run", 1, 8, 125);
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
        m_JumpTime = Globals::GetInstance() -> JUMP_TIME;
        m_RigidBody -> UnsetForce();
    }
    if (m_isJumping || !m_isGrounded){
        m_Animation -> SetProps("Samurai_Jump", 1, 2, 100);
    }
}

void Samurai::Idling(){
    m_isRunning = false;
    m_isProtecting = false;
    m_isDying = false;
    // m_isAttacking1 = false;
    // m_isAttacking2 = false;
    // m_isAttacking3 = false;
    m_RigidBody -> UnsetForce();
    m_Animation -> SetProps("Samurai_Idle", 1, 6, 150);
}

/// actions and attack

void Samurai::Protect(){
    m_RigidBody -> UnsetForce();
    if (m_isProtecting = false)
        m_Animation -> AnimationStart();
    m_isProtecting = true;
    m_Animation -> SetProps("Samurai_Protect", 1, 2, 200);
}

void Samurai::Attack1(){
    if (m_isAttacking1 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking1 == false)
        m_Animation -> AnimationStart();
    m_isAttacking1 = true;
    m_Animation -> SetProps("Samurai_Attack1", 1, 4, 180);
    if (m_Animation -> getFrame() == 3 || m_Animation -> getFrame() == 4){
        SDL_Rect Hitbox = {(int)m_Transform -> X + 80, (int)m_Transform -> Y + 65, 50, 40};
        Skeletons::GetInstance() -> checkHit(Hitbox, m_ATK * m_AttackMod1);    
        Countesses::GetInstance() -> checkHit(Hitbox, m_ATK * m_AttackMod1);
    }
}
void Samurai::Attack2(){
    if (m_isAttacking2 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking2 == false)
        m_Animation -> AnimationStart();
    m_isAttacking2 = true;
    m_Animation -> SetProps("Samurai_Attack2", 1, 5, 220);
}
void Samurai::Attack3(){
    if (m_isAttacking3 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking3 == false)
        m_Animation -> AnimationStart();
    m_isAttacking3 = true;
    m_Animation -> SetProps("Samurai_Attack3", 1, 4, 120);   
}

void Samurai::Die(){
    m_RigidBody -> UnsetForce();
    if (m_isDying == false)
        m_Animation -> AnimationStart();
    m_isDying = true;
    m_Animation -> SetProps("Samurai_Dead", 1, 8, 200);
}

void Samurai::Update(float dt){


    // SDL_Log("die here? X: %f Y: %f", m_Transform -> X, m_Transform -> Y);
    // SDL_Log("Force X: %f Y: %f", m_RigidBody ->Force().X, m_RigidBody->Force().Y);
    // SDL_Log("Acceleration X: %f Y: %f", m_RigidBody ->Acceleration().X, m_RigidBody->Acceleration().Y);
    // SDL_Log("Velocity X: %f Y: %f", m_RigidBody ->Velocity().X, m_RigidBody->Velocity().Y);
    // SDL_Log("Rigid Body X: %f Y: %f", m_RigidBody ->Position().X, m_RigidBody->Position().Y);
    
    m_RigidBody -> UnsetForce();
    
    if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_X)){
        m_HP = 0;
    }

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

        if (Input::getInstance() -> NoKeyDown()){
            Idling();
        }

        if (m_isFalling) Input::getInstance() -> LockKey();
        else Input::getInstance() -> UnlockKey();




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

        if (m_isAttacking1 == true){
            Attack1();
        }
        if (m_isAttacking2 == true){
            Attack2();
        }
        if (m_isAttacking3 == true){
            Attack3();
        }

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
    }
    //collision handling
    //X axis
    m_RigidBody -> Update(dt);
    m_LastSafePosition.X = m_Transform -> X;
    m_Transform -> X += m_RigidBody -> Position().X;
    m_Collider -> SetBox(m_Transform -> X + 40, m_Transform -> Y + 60, 35, 70);

    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
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
    m_Collider -> SetBox(m_Transform -> X + 40, m_Transform -> Y + 60, 35, 70);
    
    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
        m_isGrounded = true;
        m_Transform -> Y = m_LastSafePosition.Y;
    }
    else 
        m_isGrounded = false;
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

void Samurai::Clean(){
    TextureManager::GetInstance() -> Clean();
}