#ifndef B_VAMPIRE_H
#define B_VAMPIRE_H

#include "Characters/Character.h"
#include "Graphics/TextureManager.h"
#include "Animation/AnimationHandler.h"
#include "Physics/RigidBody.h"
#include "Physics/Collider.h"
#include "Physics/Vector2D.h"
#include "Collision/CollisionHandler.h"
#include "Globals/Globals.h"
#include "Inputs/Input.h"
#include <string>
#include <vector>
#include "Characters/Chars_Management.h"
#include "Characters/Samurai.h"
#include "Characters/Skeleton.h"

class Countess_Vampire : public Character{
    public:
        Countess_Vampire(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        // void WalkLeft();
        // void WalkRight();
        void RunLeft();
        void RunRight();
        void Idling();
        void Jump(float dt);
        inline bool isAttacking(){
            return (m_isAttacking1 || m_isAttacking2 || m_isAttacking3);
        }
        inline void stopAttack(){
            m_isAttacking1 = m_isAttacking2 = m_isAttacking3 = false;
        }
        void Attack1();
        void Attack2();
        void Attack3();
        void Die();
        void Hurt();
        
        friend class Countesses;
        
    private:
        bool m_isJumping = false;
        bool m_isGrounded = false;
        bool m_isRunning = false;
        bool m_isFalling = false;
        bool m_isAttacking1 = false;
        bool m_isAttacking2 = false;
        bool m_isAttacking3 = false;

        bool m_isDying = false;
        bool m_isAlive = true;

        int m_HP = CM::GetInstance()->GetStats("Countess").HP;
        int m_ATK = CM::GetInstance()->GetStats("Countess").ATK;
        int m_AttackMod1 = CM::GetInstance()->GetStats("Countess").mod1;
        int m_AttackMod2 = CM::GetInstance()->GetStats("Countess").mod2;
        int m_AttackMod3 = CM::GetInstance()->GetStats("Countess").mod3;


        float m_JumpTime;
        float m_JumpForce;
        // float m_AttackTime1;
        // float m_AttackTime2;
        // float m_AttackTime3;

        Vector2D m_LastSafePosition;

        Collider* m_Collider;
        AnimationHandler* m_Animation;
        RigidBody* m_RigidBody;
        
        bool m_FaceDir;//0 for left, 1 for Right 
        SDL_RendererFlip m_Dir[2] = {SDL_FLIP_HORIZONTAL, SDL_FLIP_NONE};
        
        std::string m_State;

};

class Countesses{
    public:
        static Countesses* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Countesses();
        }

        void checkHit(SDL_Rect HitBox, int damage){
            for (int i = 0; i < m_Countesses.size(); i++){
                if (CollisionHandler::GetInstance() -> CheckCollision(HitBox, m_Countesses[i] -> m_Collider->GetBox()))
                    m_Countesses[i] -> m_HP -= damage;
            }
        }

        bool checkCollision(SDL_Rect CharBox){
            for (int i = 0; i < m_Countesses.size(); i++){
                if (CollisionHandler::GetInstance() -> CheckCollision(CharBox, m_Countesses[i] -> m_Collider->GetBox()))
                    return true;
            }
            return false;
        }

        void Spawn(std::string startingState, int x, int y, int w, int h){
            Countess_Vampire* player = new Countess_Vampire(new Properties(startingState, x, y, w, h));
            m_Countesses.push_back(player);
        }
        void Clean(){
            for (int i = 0; i < m_Countesses.size(); i++){
                m_Countesses[i] -> Clean();
            }
        }
        void Update(float dt){
            for (int i = 0; i < m_Countesses.size(); i++){
                m_Countesses[i] -> Update(dt);
                if (!m_Countesses[i] -> m_isAlive){
                    m_Countesses.erase(m_Countesses.begin() + i);
                }
            }
        }
        void Draw(){
            for (int i = 0; i < m_Countesses.size(); i++){
                m_Countesses[i] -> Draw();
            }
        }
        Countess_Vampire* GetCountess(int index){
            return m_Countesses[index];
        }
    private: 
        static Countesses* s_Instance;
        std::vector<Countess_Vampire*> m_Countesses;
};

#endif