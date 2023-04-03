#include "Animation/AnimationHandler.h"
#include "Graphics/TextureManager.h"

void AnimationHandler::Update(float dt){
    int tmp = m_SpriteFrame;
    m_SpriteFrame = ((SDL_GetTicks() - m_StartTime)/m_AnimSpeed) % m_FrameNum;
    if (tmp != m_SpriteFrame) m_FrameCount ++;
}

bool AnimationHandler::ACycle(){
    if (m_FrameCount == m_FrameNum){
        m_FrameCount = 1e3 + 7;
        return true;
    }
    return false;
}

void AnimationHandler::AnimationStart(){
    m_StartTime = SDL_GetTicks();
    m_FrameCount = 0;
}
void AnimationHandler::Draw(float x, float y, int spriteWidth, int spriteHeight){
    TextureManager::getInstance() -> DrawFrame(m_textureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}
void AnimationHandler::SetProps(std::string textureID, int spriteRow, int FrameNum, int animSpeed, SDL_RendererFlip flip){
    m_textureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameNum = FrameNum;
    m_AnimSpeed = animSpeed;
    m_Flip = flip; 
}
