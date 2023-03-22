#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

class TextureManager{
    public:
        static TextureManager* getInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
        }
        bool Load(std::string fileName, std::string id); 
        void Drop(std::string id);
        void Clean();
        void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);   
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    private:
        TextureManager(){};
        std::map<std::string, SDL_Texture*> m_TextureMap;
        static TextureManager* s_Instance;   
};

#endif