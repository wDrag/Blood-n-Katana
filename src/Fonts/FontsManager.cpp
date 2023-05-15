#include "Fonts/FontsManager.h"

FontsManager* FontsManager::s_Instance = nullptr;

bool FontsManager::Load(std::string filename, std::string id, int size){
    TTF_Font* font = TTF_OpenFont(filename.c_str(), size);
    if(font == nullptr){
        SDL_Log("Failed to load font: %s", SDL_GetError());
        return false;
    }
    m_Fonts[id] = font;
    return true;
}

void FontsManager::Clean(){
    for(auto const& i : m_Fonts){
        TTF_CloseFont(i.second);
    }
    m_Fonts.clear();
}

void FontsManager::Draw(std::string id, std::string text, int x, int y, SDL_Color color, SDL_RendererFlip flip){
    SDL_Surface* surface = TTF_RenderText_Blended(m_Fonts[id], text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance() -> getRenderer(), surface);
    SDL_Rect rect = {x, y, surface -> w, surface -> h};
    SDL_FreeSurface(surface);
    SDL_RenderCopyEx(Engine::GetInstance() -> getRenderer(), texture, nullptr, &rect, 0.0, nullptr, flip);
    SDL_DestroyTexture(texture);
}