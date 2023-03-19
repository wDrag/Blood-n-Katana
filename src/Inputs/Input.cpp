#include "Inputs/Input.h"
#include "Core/engine.h"

Input* Input::s_Instance = nullptr;

Input::Input(){

}

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

void Input::KeyUp(){
    m_Keystates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown(){
    m_Keystates = SDL_GetKeyboardState(nullptr);
}