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
        
    private:
        bool m_isJumping = false;
        bool m_isGrounded = false;
        bool m_isRunning = false;
        bool m_isFalling = false;
        bool m_isProtecting = false;
        bool m_isAttacking1 = false;
        bool m_isAttacking2 = false;
        bool m_isAttacking3 = false;

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

#endif