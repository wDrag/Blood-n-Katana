#ifndef PLAY_H
#define PLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "GameStates/GameState.h"
#include "Button/Button.h"
#include "Map/GameMap.h"

class Play : public GameState{
    private:
        void toGameOver();
        void toVictory();

        void Pause();
        void Continue();

        bool m_Pause;
        bool m_isDefeated;
        bool m_isVictory;

        int numSkeletonsKilled;
        int numSkeletonSpawned;
        int numBoss;
        Button* B_Pause;

    public:
        Play();
        virtual void Init();
        virtual void Update(float dt);
        virtual void Render();
        virtual void Quit();
        void Events();

};

#endif