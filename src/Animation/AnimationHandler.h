#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include <string>
#include <SDL2/SDL.h>

class AnimationHandler{
    public: 
        AnimationHandler(){}

        void Update(float dt);
        void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetDir(SDL_RendererFlip Dir);
        void SetProps(std::string textureID, int spriteRow, int FrameCount, int animSpeed);
        void AnimationStart();
        bool ACycle();
        bool UnderCycle();
        bool OverCycle();
        bool NCycle(int num);
    private:
        int m_SpriteRow, m_SpriteFrame;
        int m_AnimSpeed, m_FrameCount;
        int m_FrameNum;
        std::string m_textureID;
        Uint32 m_StartTime = 0;
};

#endif