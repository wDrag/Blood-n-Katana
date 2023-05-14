#include "Characters/Boss_Vampire.h"
#include "Camera/Camera.h"
#include <SDL2/SDL.h>

#define right 1
#define left -1
#define up   -1
#define down  1

Countesses* Countesses::s_Instance = nullptr;
BloodChargesManager* BloodChargesManager::s_Instance = nullptr;

Countess_Vampire::Countess_Vampire(Properties* props) : Character(props){

    m_JumpTime = Globals::GetInstance() -> JUMP_TIME;
    m_JumpForce = Globals::GetInstance() -> JUMP_FORCE * 1.5;

    m_Collider = new Collider;
    m_Collider -> SetBuffer(0, 0, 0, 0);
 
    m_RigidBody = new RigidBody();
    m_RigidBody -> setGravity(5.0f);
    
    m_FaceDir = 0;

    m_isAlive = true;

    int m_HP = CM::GetInstance()->GetStats("Countess").HP;
    
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
    if (m_isAttacking1 == false){
        m_Animation -> AnimationStart();
        BloodChargesManager::GetInstance() -> Spawn("Countess_Particle1", m_Transform -> X, m_Transform -> Y, Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, m_FaceDir, 1, m_ATK * m_AttackMod1, 0);
    }
    m_isAttacking1 = true;
    m_Animation -> SetProps("Countess_Attack1", 1, 8, 150);
}
void Countess_Vampire::Attack2(){
    if (m_isAttacking2 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking2 == false){
        m_Animation -> AnimationStart();
        BloodChargesManager::GetInstance() -> Spawn("Countess_Particle1", m_Transform -> X, m_Transform -> Y, Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, m_FaceDir, 1, m_ATK * m_AttackMod1, 0);
    }
    m_isAttacking2 = true;
    m_Animation -> SetProps("Countess_Attack2", 1, 7, 150);
}
void Countess_Vampire::Attack3(){
    if (m_isAttacking3 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking3 == false){
        m_Animation -> AnimationStart();
        BloodChargesManager::GetInstance() -> Spawn("Countess_Particle1", m_Transform -> X, m_Transform -> Y, Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, m_FaceDir, 1, m_ATK * m_AttackMod1, 0);
    }
    m_isAttacking3 = true;
    m_Animation -> SetProps("Countess_Attack3", 1, 10, 150);   
}

void Countess_Vampire::Die(){
    m_RigidBody -> UnsetForce();
    if (m_isDying == false)
        m_Animation -> AnimationStart();
    m_isDying = true;
    m_Animation -> SetProps("Countess_Dead", 1, 9, 200);
}

void Countess_Vampire::Hurt(){
    
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

        if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_SPACE)){
            Jump(dt);
        }

        if (m_Animation -> ACycle() && isAttacking() == true){
            stopAttack();
        }

        //move
        if (Input::getInstance() -> GetKeyDown(SDL_SCANCODE_SPACE) == false){
           Idling();   
        }
        
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
    m_Collider -> SetBox(m_Transform -> X + 43, m_Transform -> Y + 47, 40, 78);

    if (CollisionHandler::GetInstance() -> MapCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }
    if (Players::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }
    if (Countesses::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_Transform -> X = m_LastSafePosition.X;
    }

    //Y axis
    m_RigidBody -> Update(dt);
    m_LastSafePosition.Y = m_Transform -> Y;
    m_Transform -> Y += m_RigidBody -> Position().Y;
    m_Collider -> SetBox(m_Transform -> X + 43, m_Transform -> Y + 47, 40, 78);
    
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
    if (Players::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_isGrounded = true;
        m_Transform -> Y = m_LastSafePosition.Y;
    }

    ///////
    
    m_Origin -> X = m_Transform -> X + m_Width/2;
    m_Origin -> Y = m_Transform -> Y + m_Height/2;

    m_Animation -> Update(dt);
}

void Countess_Vampire::Clean(){
}

BloodCharges::BloodCharges(Properties* props, bool Dir, int Type, int ATK, bool Down) : Character(props){
    m_HP = 1;
    m_ATK = ATK;

    m_Collider = new Collider;
    m_Collider -> SetBuffer(0, 0, 0, 0);
 
    m_RigidBody = new RigidBody();
    m_RigidBody -> setGravity(0);

    m_Animation = new AnimationHandler();

    m_FaceDir = Dir;

    m_Down = Down;

    m_Type = Type;
    switch (m_Type)
    {
    case 1:
        m_Animation -> SetProps("Countess_Particle1", 1, 3, 100);
        break;
    case 2:
        m_Animation -> SetProps("Countess_Particle2", 1, 3, 100);
        break;
    case 3:
        m_Animation -> SetProps("Countess_Particle3", 1, 3, 100);
        break;
    default:
        break;
    }
}

void BloodCharges::Draw(){
    m_Animation -> Draw(m_Transform -> X, m_Transform -> Y, m_Width, m_Height, m_Dir[m_FaceDir]);
}

void BloodCharges::Right(){
    m_RigidBody -> ApplyForceX(5.0f);
}

void BloodCharges::Left(){
    m_RigidBody -> ApplyForceX(-5.0f);
}

void BloodCharges::Down(){
    m_RigidBody -> ApplyForceY(10.0f);
}

void BloodCharges::Update(float dt){
    // m_RigidBody -> UnsetForce();
    
    if (m_Down){
        Down();
    }
    else {
        if (m_FaceDir == 1){
            Right();
        }
        else {
            Left();
        }
    }

    m_RigidBody -> Update(dt);
    m_Transform -> X += m_RigidBody -> Position().X;
    m_Transform -> Y += m_RigidBody -> Position().Y;

    switch (m_Type)
    {
    case 1:
        m_Collider -> SetBox(m_Transform -> X + 6, m_Transform -> Y + 18, 26, 10);
        break;
    case 2:
        m_Collider -> SetBox(m_Transform -> X + 25, m_Transform -> Y + 17, 11, 12);
        break;
    case 3:
        m_Collider -> SetBox(m_Transform -> X + 10, m_Transform -> Y + 20, 32, 8);
        break;
    default:
        break;
    }

    Players::GetInstance() -> checkHit(m_Collider -> GetBox(), m_ATK);
    if (Players::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_HP = 0;
    }  
    Players::GetInstance() -> DealDMG();
    m_Animation -> Update(dt);

    m_Origin -> X = m_Transform -> X + m_Width/2;
    m_Origin -> Y = m_Transform -> Y + m_Height/2;
}

void BloodCharges::Clean(){

}