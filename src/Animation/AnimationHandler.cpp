#include "Animation/AnimationHandler.h"
#include "Graphics/TextureManager.h"

void AnimationHandler::Update(float dt){
    m_SpriteFrame = ((SDL_GetTicks() - m_StartTime)/m_AnimSpeed) % m_FrameCount;
}

void AnimationHandler::AnimationStart(){
    m_StartTime = SDL_GetTicks();
   
}
void AnimationHandler::Draw(float x, float y, int spriteWidth, int spriteHeight){
    TextureManager::getInstance() -> DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}
void AnimationHandler::SetProps(std::string textureID, int spriteRow, int FrameCount, int animSpeed, SDL_RendererFlip flip){
    m_textureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = FrameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip; 
}
