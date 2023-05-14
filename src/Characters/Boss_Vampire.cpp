#include "Characters/Boss_Vampire.h"
#include "Camera/Camera.h"
#include <SDL2/SDL.h>
#include <cmath>

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

    m_HP_Bar_MAX = {(int)m_Transform -> X + 15, (int)m_Transform -> Y + 30, 96, 8};
    m_HP_Bar = m_HP_Bar_MAX;

    m_isAlive = true;

    int m_HP = CM::GetInstance()->GetStats("Countess").HP;
    
    m_Animation = new AnimationHandler();
    Idling();
}

void Countess_Vampire::Draw(){
    SDL_SetRenderDrawColor(Engine::GetInstance() -> getRenderer(), 77, 21, 38, 255);
    SDL_RenderFillRect(Engine::GetInstance() -> getRenderer(), &m_HP_Bar_MAX);
    SDL_SetRenderDrawColor(Engine::GetInstance() -> getRenderer(), 186, 49, 33, 255);
    SDL_RenderFillRect(Engine::GetInstance() -> getRenderer(), &m_HP_Bar);
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
    }
    m_isAttacking1 = true;
    m_Animation -> SetProps("Countess_Attack1", 1, 8, 250);
}
void Countess_Vampire::Attack2(){
    if (m_isAttacking2 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking2 == false){
        m_Animation -> AnimationStart();
    }
    m_isAttacking2 = true;
    m_Animation -> SetProps("Countess_Attack2", 1, 7, 250);
}

void Countess_Vampire::AttackEX(){
    if (m_isAttackingEX == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttackingEX == false){
        m_Animation -> AnimationStart();
    }
    m_isAttackingEX = true;
    m_Animation -> SetProps("Countess_Attack2", 1, 7, 250);
}

void Countess_Vampire::Attack3(){
    if (m_isAttacking3 == false && isAttacking()) return;
    m_RigidBody -> UnsetForce();
    if (m_isAttacking3 == false){
        m_Animation -> AnimationStart();
    }
    m_isAttacking3 = true;
    m_Animation -> SetProps("Countess_Attack3", 1, 10, 300);   
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
   
    m_HP_Bar.w = m_HP * m_HP_Bar_MAX.w / CM::GetInstance() -> GetStats("Countess").HP;
    if (m_Animation -> ACycle() && m_isDying == true){
        m_isDying = false;
        m_isAlive = false;
        return;
    }

    if (!m_isDying){

        m_RigidBody -> UnsetForce();    

        if (m_Animation -> ACycle() && isAttacking() == true){
            if (m_isAttacking1){
                BloodChargesManager::GetInstance() -> Spawn("Countess_Particle1", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, m_Transform -> X, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y + 25, m_FaceDir, 1, m_ATK * m_AttackMod1, 0);
            }

            if (m_isAttacking2){
                BloodChargesManager::GetInstance() -> Spawn("Countess_Particle2", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X - 25, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y - 250, m_FaceDir, 2, m_ATK * m_AttackMod2, 1);
            }

            if (m_isAttacking3){
                int xOffset = 0;
                if (m_FaceDir == 0)
                    xOffset = -400;
                else if (m_FaceDir == 1)
                    xOffset = 400;
                BloodChargesManager::GetInstance() -> Spawn("Countess_Particle3", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X + xOffset, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y + 30, m_FaceDir, 3, m_ATK * m_AttackMod3, 0);
            }

            if (m_isAttackingEX){
                // BloodChargesManager::GetInstance() -> Spawn("Countess_Particle2", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X - 70, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y - 250, m_FaceDir, 2, m_ATK * m_AttackMod2, 1);
                BloodChargesManager::GetInstance() -> Spawn("Countess_Particle2", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X - 50, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y - 250, m_FaceDir, 2, m_ATK * m_AttackMod2, 1);
                BloodChargesManager::GetInstance() -> Spawn("Countess_Particle2", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X - 25, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y - 250, m_FaceDir, 2, m_ATK * m_AttackMod2, 1);
                BloodChargesManager::GetInstance() -> Spawn("Countess_Particle2", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y - 250, m_FaceDir, 2, m_ATK * m_AttackMod2, 1);
                BloodChargesManager::GetInstance() -> Spawn("Countess_Particle2", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X + 25, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y - 250, m_FaceDir, 2, m_ATK * m_AttackMod2, 1);
                // BloodChargesManager::GetInstance() -> Spawn("Countess_Particle2", Globals::GetInstance() -> ProjectileFrameSizeX, Globals::GetInstance() -> ProjectileFrameSizeY, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X + 75, Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> Y - 250, m_FaceDir, 2, m_ATK * m_AttackMod2, 1);
            }
            stopAttack();
        }

        //move

        int px = Players::GetInstance() -> GetPlayer(0) -> GetOrigin() -> X;
        if (m_isGrounded){
            if (px > m_Origin -> X){
                m_FaceDir = 1;
            }
            else {
                m_FaceDir = 0;
            }
            int rnd = Globals::GetInstance() -> Random(1, 50);
            switch (rnd)
            {
            case 1:
                if (isAttacking() == false && abs(px - m_Origin -> X) >= 300)
                    Attack1();
                break;
            case 2:
                if (isAttacking() == false)
                    Globals::GetInstance() -> Random (0, 20) == 0 ? AttackEX() :
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
            if (m_Type == 3)
                Left();
            else
                Right();
        }
        else {
            if (m_Type == 3)
                Right();
            else
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

    Players::GetInstance() -> checkHitProjectile(m_Collider -> GetBox(), m_ATK);
    if (Players::GetInstance() -> checkCollision(m_Collider -> GetBox())){
        m_HP = 0;
    }  
    m_Animation -> Update(dt);

    m_Origin -> X = m_Transform -> X + m_Width/2;
    m_Origin -> Y = m_Transform -> Y + m_Height/2;
}

void BloodCharges::Clean(){

}