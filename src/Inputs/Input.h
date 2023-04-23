#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>


enum Axis {HORIZONTAL, VERTICAL};

class Input{
    public:
        static Input* getInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        bool NoKeyDown();

        void LockKey();
        void UnlockKey();

        int GetAxisKey(Axis axis);
        int GetAttackKey();

    private:
        static bool m_KeyLocked;
        Input(){};
        void KeyUp();
        void KeyDown();
        static Input* s_Instance;
        const Uint8* m_Keystates;
};  

#endif