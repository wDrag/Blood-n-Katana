#ifndef FONTS_MANAGER_H
#define FONTS_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include "Core/Engine.h"

class FontsManager{
public:
    static FontsManager* GetInstance(){
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new FontsManager();
    }
    bool Load(std::string filename, std::string id , int size);
    void Clean();
    void Draw(std::string id, std::string text, int x, int y, SDL_Color color = {255, 255, 255, 255}, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    static FontsManager* s_Instance;
    std::map<std::string, TTF_Font*> m_Fonts;
};

#endif