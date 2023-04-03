#ifndef SAMURAI_H
#define SAMURAI_H

#include "Characters/Character.h"
#include "Animation/AnimationHandler.h"
#include "Physics/RigidBody.h"
#include <string>

class Samurai : public Character{
    public:
        Samurai(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        void WalkLeft();
        void WalkRight();
        void Idling();
        void Jump();
        void Protect();
        void Attack1();
        void Attack2();
        void Attack3();
        
    private:
        AnimationHandler* m_Animation;
        RigidBody* m_RigidBody;
        bool m_FaceDir;//0 for left, 1 for Right 
        SDL_RendererFlip m_Dir[2] = {SDL_FLIP_HORIZONTAL, SDL_FLIP_NONE};
        std::string m_State;

};

#endif