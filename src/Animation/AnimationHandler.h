#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include <string>
#include <SDL2/SDL.h>

class AnimationHandler{
    public: 
        AnimationHandler(){}

        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight);
        void SetProps(std::string textureID, int spriteRow, int FrameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    private:
        int m_SpriteRow, m_SpriteFrame;
        int m_AnimSpeed, m_FrameCount;
        std::string m_textureID;
        SDL_RendererFlip m_Flip;
};

#endif