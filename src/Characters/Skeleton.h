#ifndef SKELETON_H
#define SKELETON_H

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
#include "Characters/Chars_Management.h"


class Skeleton : public Character{
    public:
        Skeleton(Properties* props);
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
        void WalkLeft();
        void WalkRight();
        void Attack1();
        void Attack2();
        void Attack3();
        void Die();

        friend class Skeletons;
        
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


        int m_HP = CM::GetInstance()->GetStats("Skeleton").HP;
        int m_ATK = CM::GetInstance()->GetStats("Skeleton").ATK;
        int m_AttackMod1 = CM::GetInstance()->GetStats("Skeleton").mod1;
        int m_AttackMod2 = CM::GetInstance()->GetStats("Skeleton]").mod2;
        int m_AttackMod3 = CM::GetInstance()->GetStats("Skeleton]").mod3;


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

class Skeletons{
    public:
        static Skeletons* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Skeletons();
        }
        void Spawn(std::string startingState, int x, int y, int w, int h){
            Skeleton* player = new Skeleton(new Properties(startingState, x, y, w, h));
            m_Skeletons.push_back(player);
        }
        void Clean(){
            for (int i = 0; i < m_Skeletons.size(); i++){
                m_Skeletons[i] -> Clean();
            }
        }
        void Update(float dt){
            for (int i = 0; i < m_Skeletons.size(); i++){
                m_Skeletons[i] -> Update(dt);
                if (!m_Skeletons[i] -> m_isAlive){
                    m_Skeletons.erase(m_Skeletons.begin() + i);
                }
            }
        }
        void Draw(){
            for (int i = 0; i < m_Skeletons.size(); i++){
                m_Skeletons[i] -> Draw();
            }
        }
        Skeleton* GetSkeleton(int index){
            return m_Skeletons[index];
        }
    private: 
        static Skeletons* s_Instance;
        std::vector<Skeleton*> m_Skeletons;
};

#endif