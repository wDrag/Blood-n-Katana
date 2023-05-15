#ifndef VICTORY_H
#define VICTORY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "GameStates/GameState.h"
#include "Button/Button.h"

class Victory: public GameState{
    public:
        Victory(){};
        void Events();
        virtual void Init();
        virtual void Update(float dt);
        virtual void Render();
        void toPlay();
        void Quit();

    private:
        Button* B_Restart;
        Button* B_Quit;

};

#endif