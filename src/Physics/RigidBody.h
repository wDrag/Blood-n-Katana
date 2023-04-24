#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Physics/Vector2D.h"

//global modifiers 0.5

#define UNI_MASS 1.0f
#define GRAVITY 4.9f
#define START_POS_X 200
#define START_POS_Y 450

class RigidBody{
    public:
        RigidBody() {
            m_Mass = UNI_MASS;
            m_Gravity = GRAVITY;
        }

        inline void setMass(float mass){m_Mass = mass;}
        inline void setGravity(float gravity){m_Gravity = gravity;}
        //Force
        inline void ApplyForce(Vector2D F) {m_Force = F;}
        inline void ApplyForceX(float Fx) {m_Force.X = Fx;}
        inline void ApplyForceY(float Fy) {m_Force.Y = Fy;}
        inline void UnsetForce() {m_Force = Vector2D();}
        //Friction
        inline void ApplyFriction(Vector2D Fr) {m_Friction = Fr;}
        inline void UnsetFriction() {m_Friction = Vector2D();}

        inline float getMass(){return m_Mass;}
        inline float getGravity(){return m_Gravity;}
        inline Vector2D Position(){return m_Position;}
        inline Vector2D Velocity(){return m_Velocity;}
        inline Vector2D Acceleration(){return m_Acceleration;}
        
        void Update(float dt){
            m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
            m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
            m_Velocity = m_Acceleration * dt;
            m_Position = m_Velocity * dt;
        }
    private:
        float m_Mass;
        float m_Gravity;

        Vector2D m_Force = Vector2D();
        Vector2D m_Friction = Vector2D();

        Vector2D m_Position = Vector2D(START_POS_X, START_POS_Y);
        Vector2D m_Velocity = Vector2D();
        Vector2D m_Acceleration = Vector2D();
};

#endif