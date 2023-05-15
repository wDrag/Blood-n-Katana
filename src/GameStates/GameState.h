#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include "Button/Button.h"

class GameState{
    public:
        virtual void Init(){};
        virtual void Update(float dt){};
        virtual void Render(){};
        virtual void Quit(){};
};

#endif