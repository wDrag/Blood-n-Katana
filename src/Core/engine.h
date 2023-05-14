#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Map/GameMap.h"

class Engine{
    public:
        static Engine* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
        }
        bool Init();
        void Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline bool isRunning() { return m_isRunning; }
        inline SDL_Renderer* getRenderer() { return m_Renderer; }
        inline GameMap* GetMap() {return m_LevelMap;}
    private:
        bool m_isRunning;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        Engine(){}
        static Engine* s_Instance;
        GameMap* m_LevelMap;
};

#endif