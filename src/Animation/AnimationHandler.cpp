#include "Animation/AnimationHandler.h"
#include "Graphics/TextureManager.h"

void AnimationHandler::Update(float dt){
    int tmp = m_SpriteFrame;
    m_SpriteFrame = ((SDL_GetTicks() - m_StartTime)/m_AnimSpeed) % m_FrameNum;
    if (tmp != m_SpriteFrame) m_FrameCount ++;
}

bool AnimationHandler::UnderCycle(){
    if (m_FrameCount < m_FrameNum){
        return true;
    }
    return false;
}

bool AnimationHandler::ACycle(){
    if (m_FrameCount == m_FrameNum){
        return true;
    }
    return false;
}

bool AnimationHandler::NCycle(int num){
    if (m_FrameCount == m_FrameNum * num){
        return true;
    }
    return false;
}

bool AnimationHandler::OverCycle(){
    if (m_FrameCount > m_FrameNum){
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
void AnimationHandler::SetDir(SDL_RendererFlip flip){
    m_Flip = flip;
}
