#include "Characters/Samurai.h"
#include "Graphics/TextureManager.h"
#include <SDL2/SDL.h>


Samurai::Samurai(Properties* props) : Character(props){
    m_Row = 1;
    m_FrameCount = 4;
    m_AnimSpeed = 100;
}

void Samurai::Draw(){
    TextureManager::getInstance() -> DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

void Samurai::Update(float dt){
    m_Frame = (SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void Samurai::Clean(){
    TextureManager::getInstance() -> Clean();
}