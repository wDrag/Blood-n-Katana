#include "Graphics/TextureManager.h"
#include "Core/engine.h"
#include "Camera/Camera.h"
// #include <iostream>

TextureManager* TextureManager::s_Instance = nullptr;   

bool TextureManager::Load(std::string id, std::string fileName){
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface == nullptr){
        SDL_Log("Failed to load image: %s, %s", fileName.c_str(), IMG_GetError());
        return false;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance() -> getRenderer(), surface);
    if (texture == nullptr){
        SDL_Log("Failed to create texture: %s, %s", fileName.c_str(), SDL_GetError());
        return false;
    }  

    m_TextureMap[id] = texture;

    return true;
}

bool TextureManager::ParseTextures(std::string source, std::string value){
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()){
        std::cout << "Failed to load: " << source << '\n';
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    for(TiXmlElement * e = root -> FirstChildElement(); e!= nullptr; e = e -> NextSiblingElement()){
        if (e -> Value() != value) continue;
        for (TiXmlElement * e1 = e -> FirstChildElement(); e1 != nullptr; e1 = e1 -> NextSiblingElement()){
            std::string id = e1->Attribute("id");
            std::string src = e1->Attribute("source");
            Load(id, src);
        }
    }
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip){
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance() -> getRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip){
    SDL_Rect srcRect = {width * frame, height * (row - 1), width, height};
    Vector2D cam = Camera::GetInstance() -> GetPosition();
    SDL_Rect destRect = {x - (int)cam.X, y - (int)cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance() -> getRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int col, SDL_RendererFlip flip){
    SDL_Rect srcRect = {tileSize * col, tileSize * row, tileSize, tileSize};
    Vector2D cam = Camera::GetInstance() -> GetPosition();
    SDL_Rect destRect = {x * tileSize - (int)cam.X, y * tileSize - (int)cam.Y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance() -> getRenderer(), m_TextureMap[tilesetID], &srcRect, &destRect, 0, nullptr, flip);
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

// void TextureManager::checkMap(){
   
//     for(auto x: m_TextureMap){
//         std::cout << x.first << '\n';
//     }
// }
