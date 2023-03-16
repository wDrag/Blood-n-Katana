#include "Graphics/TextureManager.h"
#include "Core/engine.h"

TextureManager* TextureManager::s_Instance = nullptr;   

bool TextureManager::Load(std::string fileName, std::string id){
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface == nullptr){
        SDL_Log("Failed to load image: %s, %s", fileName.c_str(), IMG_GetError());
        return false;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::getInstance() -> getRenderer(), surface);
    if (texture == nullptr){
        SDL_Log("Failed to create texture: %s, %s", fileName.c_str(), SDL_GetError());
        return false;
    }  

    m_TextureMap[id] = texture;

    return true;
}
void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip){
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::getInstance() -> getRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip){
    SDL_Rect srcRect = {width * frame, height * (row - 1), width, height};
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::getInstance() -> getRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}
void TextureManager::Drop(std::string id){
    if (m_TextureMap[id] != nullptr){
        SDL_DestroyTexture(m_TextureMap[id]);
        m_TextureMap.erase(id);
    }
}
void TextureManager::Clean(){
    for (auto& texture : m_TextureMap){
        SDL_DestroyTexture(texture.second);
    }
    m_TextureMap.clear();
}
