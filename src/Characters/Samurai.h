#ifndef SAMURAI_H
#define SAMURAI_H

#include "Characters/Character.h"
#include "Graphics/TextureManager.h"
#include "Animation/AnimationHandler.h"
#include "Physics/RigidBody.h"
#include "Physics/Collider.h"
#include "Physics/Vector2D.h"
#include "Collision/CollisionHandler.h"
#include "Inputs/Input.h"
#include "Globals/Globals.h"
#include <string>
#include <vector>
#include "Characters/Chars_Management.h"
#include "Characters/Boss_Vampire.h"
#include "Characters/Skeleton.h"


class Samurai : public Character{
    public:
        Samurai(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        // void WalkLeft();
        // void WalkRight();
        void RunLeft();
        void RunRight();
        void Idling();
        void Jump(float dt);
        void Die();
        void Hurt();
        inline bool isAttacking(){
            return (m_isAttacking1 || m_isAttacking2 || m_isAttacking3);
        }
        inline void stopAttack(){
            m_isAttacking1 = m_isAttacking2 = m_isAttacking3 = false;
        }
        void Protect();
        void Attack1();
        void Attack2();
        void Attack3();

        friend class Players;

    private:
        bool m_isJumping = false;
        bool m_isGrounded = false;
        bool m_isRunning = false;
        bool m_isFalling = false;
        bool m_isProtecting = false;
        bool m_isAttacking1 = false;
        bool m_isAttacking2 = false;
        bool m_isAttacking3 = false;
        bool m_isHurting = false;

        int m_DamageTaking = 0;

        bool m_isDying = false;
        bool m_isAlive = true;

       
        int m_HP = CM::GetInstance()->GetStats("Samurai").HP;
        int m_ATK = CM::GetInstance()->GetStats("Samurai").ATK;
        float m_AttackMod1 = CM::GetInstance()->GetStats("Samurai").mod1;
        float m_AttackMod2 = CM::GetInstance()->GetStats("Samurai").mod2;
        float m_AttackMod3 = CM::GetInstance()->GetStats("Samurai").mod3;

        float m_JumpTime;
        float m_JumpForce;
        // float m_AttackTime1;
        // float m_AttackTime2;
        // float m_AttackTime3;

        Vector2D m_LastSafePosition;

        Collider* m_Collider;
        AnimationHandler* m_Animation;
        RigidBody* m_RigidBody;

        SDL_Rect m_HP_Bar;
        SDL_Rect m_HP_Bar_MAX;
        
        bool m_FaceDir;//0 for left, 1 for Right 
        SDL_RendererFlip m_Dir[2] = {SDL_FLIP_HORIZONTAL, SDL_FLIP_NONE};

};

class Players{
    public:
        static Players* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Players();
        }

        void checkHit(SDL_Rect HitBox, int damage){
            for (int i = 0; i < m_Players.size(); i++){
                if (CollisionHandler::GetInstance() -> CheckCollision(HitBox, m_Players[i] -> m_Collider->GetBox())){
                    if (!m_Players[i] -> m_isProtecting){
                        m_Players[i] -> m_DamageTaking = damage;
                        m_Players[i] -> Hurt();
                    }
                    else m_Players[i] -> m_DamageTaking = damage/4;
                }
            }
        }
        void checkHitProjectile(SDL_Rect HitBox, int damage){
            for (int i = 0; i < m_Players.size(); i++){
                if (CollisionHandler::GetInstance() -> CheckCollision(HitBox, m_Players[i] -> m_Collider->GetBox())){
                    if (!m_Players[i] -> m_isProtecting){
                        m_Players[i] -> m_HP -= damage;
                        m_Players[i] -> Hurt();
                    }
                    else m_Players[i] -> m_HP -= damage/4;
                }
            }
        }

        void DealDMG(){
            for (int i = 0; i < m_Players.size(); i++){
                m_Players[i] -> m_HP -= m_Players[i] -> m_DamageTaking;
                if (m_Players[i] -> m_DamageTaking > 0)
                    m_Players[i] -> m_DamageTaking = 0;
            }
        }

        bool checkCollision(SDL_Rect CharBox){
            for (int i = 0; i < m_Players.size(); i++){
                if (CollisionHandler::GetInstance() -> CheckCollision(CharBox, m_Players[i] -> m_Collider->GetBox()))
                    return true;
            }
            return false;
        }
        
        void Spawn(std::string startingState, int w, int h, int x, int y){
            Samurai* player = new Samurai(new Properties(startingState, w, h, x, y));
            m_Players.push_back(player);
        }
        void Clean(){
            for (int i = 0; i < m_Players.size(); i++){
                m_Players[i] -> Clean();
            }
        }
        void Update(float dt){
            for (int i = m_Players.size() - 1; i >= 0; i--){
                m_Players[i] -> Update(dt);
                if (!m_Players[i] -> m_isAlive){
                    m_Players.erase(m_Players.begin() + i);
                }
            }
        }
        void Draw(){
            for (int i = 0; i < m_Players.size(); i++){
                m_Players[i] -> Draw();
            }
        }
        Samurai* GetPlayer(int index){
            return m_Players[index];
        }
    private: 
        static Players* s_Instance;
        std::vector<Samurai*> m_Players;
};

#endif