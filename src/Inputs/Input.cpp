#include "Inputs/Input.h"
#include "Core/engine.h"

Input* Input::s_Instance = nullptr;

bool Input::m_KeyLocked = 0;

void Input::Listen(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT : 
                Engine::GetInstance() -> Quit(); 
                break;
            case SDL_KEYDOWN :
                if (event.key.repeat == 0)
                    KeyDown(); 
                break;
            case SDL_KEYUP : 
                if (event.key.repeat == 0)
                    KeyUp(); 
                break;
        }
    }
}

void Input::LockKey(){
    m_KeyLocked = true;
}

void Input::UnlockKey(){
    m_KeyLocked = false;
}

bool Input::GetKeyDown(SDL_Scancode key){
    if (m_KeyLocked && key != SDL_SCANCODE_W && key != SDL_SCANCODE_UP) return false;
    return (m_Keystates[key] == 1);
}

bool Input::NoKeyDown(){
    if (GetAxisKey(VERTICAL) == -1) return false;
    if (m_KeyLocked) return true;
    SDL_Scancode Key_List [] = {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_KP_1, SDL_SCANCODE_KP_2, SDL_SCANCODE_KP_3,SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_J, SDL_SCANCODE_K, SDL_SCANCODE_L};
    for (SDL_Scancode key : Key_List){
        if (m_Keystates[key] == 1){
            return false;
        }
    }
    return true;
}

void Input::KeyUp(){
    m_Keystates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown(){
    m_Keystates = SDL_GetKeyboardState(nullptr);
}

int Input::GetAxisKey(Axis axis){
    if (axis == HORIZONTAL){
        if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT))
            return 1;
        if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT))
            return -1;
    }
    if (axis == VERTICAL){
        if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP))
            return -1;
        if (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN))
            return 1;
    }
    return 0;
}

int Input::GetAttackKey(){
    if (GetKeyDown(SDL_SCANCODE_J) || GetKeyDown(SDL_SCANCODE_KP_1))
        return 1;
    if (GetKeyDown(SDL_SCANCODE_K) || GetKeyDown(SDL_SCANCODE_KP_2))
        return 2;
    if (GetKeyDown(SDL_SCANCODE_L) || GetKeyDown(SDL_SCANCODE_KP_3))
        return 3;
    return 0;
}