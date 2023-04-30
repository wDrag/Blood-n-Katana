#ifndef GLOBALS_H
#define GLOBALS_H

class Globals{
    public:
        static Globals* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Globals();
        }
        const float JUMP_TIME = 20.0f;
        const float JUMP_FORCE = 9.0f;
        const int HumanoidFrameSize = 128;
        const int ProjectileFrameSize = 48;
        const int StartingX = 200;
        const int StartingY = 450;
        const int SCREEN_WIDTH = 1440;
        const int SCREEN_HEIGHT = 864;
    private:
        Globals(){};
        static Globals* s_Instance;
};

#endif