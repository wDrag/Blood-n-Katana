#include "Inputs/Input.h"
#include "Core/engine.h"

Input* Input::s_Instance = nullptr;

void Input::Listen(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT : Engine::getInstance() -> Quit(); break;
            case SDL_KEYDOWN : KeyDown(); break;
            case SDL_KEYUP : KeyUp(); break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key){
    return (m_Keystates[key] == 1);
}

bool Input::NoKeyDown(){
    SDL_Scancode Key_List [] = {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_J, SDL_SCANCODE_K, SDL_SCANCODE_L};
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