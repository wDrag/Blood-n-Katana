#ifndef HOME_H
#define HOME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "GameStates/GameState.h"
#include "Button/Button.h"

class Home: public GameState{
    public:
        Home(){};
        void Events();
        virtual void Init();
        virtual void Update(float dt);
        virtual void Render();
        void toPlay();
        void Quit();

    private:
        Button* B_Play;
        Button* B_Quit;

};

#endif