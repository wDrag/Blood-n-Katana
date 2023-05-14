#ifndef GLOBALS_H
#define GLOBALS_H

#include <random>

class Globals{
    public:
        static Globals* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Globals();
        }
        const float JUMP_TIME = 20.0f;
        const float JUMP_FORCE = 9.0f;
        const int HumanoidFrameSize = 128;
        const int ProjectileFrameSizeX = 64;
        const int ProjectileFrameSizeY = 48;
        const int StartingX = 200;
        const int StartingY = 600;
        const int StartingXB = 1840;
        const int StartingYB = 540;
        const int SCREEN_WIDTH = 1440;
        const int SCREEN_HEIGHT = 864;

        int Random(int min, int max){
            return rand() % (max - min + 1) + min;
        }

    private:
        Globals(){};
        static Globals* s_Instance;
};

#endif