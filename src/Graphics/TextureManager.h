#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include "TinyXML/tinyxml.h"

class TextureManager{
    public:
        static TextureManager* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
        }
        bool Load(std::string id, std::string fileName); 
        bool ParseTextures(std::string source, std::string value);
        void Drop(std::string id);
        void Clean();
        void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);   
        void TextureManager::DrawButton(std::string id, int x, int y, int width, int height, int dstWidth, int dstHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE);
        // void checkMap();
    private:
        TextureManager(){};
        std::map<std::string, SDL_Texture*> m_TextureMap;
        static TextureManager* s_Instance;   
};

#endif