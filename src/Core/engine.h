#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine{
    public:
        static Engine* getInstance(){
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
    private:
        bool m_isRunning;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        Engine(){}
        static Engine* s_Instance;
};

#endif