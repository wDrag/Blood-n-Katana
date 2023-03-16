#ifndef SAMURAI_H
#define SAMURAI_H

#include "Characters/Character.h"

class Samurai : public Character{
    public:
        Samurai(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
    private:
        int m_Row, m_Frame, m_FrameCount;
        int m_AnimSpeed;
};

#endif