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
#include <string>


#define JUMP_TIME 20.0f
#define JUMP_FORCE 9.0f

class Samurai : public Character{
    public:
        Samurai(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        void WalkLeft();
        void WalkRight();
        void RunLeft();
        void RunRight();
        void Idling();
        void Jump(float dt);
        // void Protect();
        // void Attack1();
        // void Attack2();
        // void Attack3();
        
    private:
        bool m_IsJumping;
        bool m_Jumpable;

        float m_JumpTime;
        float m_JumpForce;

        Vector2D m_LastSafePosition;

        Collider* m_Collider;
        AnimationHandler* m_Animation;
        RigidBody* m_RigidBody;
        
        bool m_FaceDir;//0 for left, 1 for Right 
        SDL_RendererFlip m_Dir[2] = {SDL_FLIP_HORIZONTAL, SDL_FLIP_NONE};
        
        std::string m_State;

};

#endif