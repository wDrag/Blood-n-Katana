#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "Inputs/Input.h"
#include "Camera/Camera.h"
#include "Graphics/TextureManager.h"

enum button_state{
    NORMAL = 0,
    HOVER = 1,
    CLICKED = 2
};

class Button{
    public:
        Button(){
            m_State = NORMAL;
        }
        Button(int x, int y, std::string textureID){
            m_Position.x = x;
            m_Position.y = y;
            m_Position.w = 214;
            m_Position.h = 215;
            m_TextureID = textureID;
            m_State = NORMAL;
        }

        void ChangeTexture(std::string textureID){
            m_TextureID = textureID;
        }

        void Draw(){
           TextureManager::GetInstance() -> DrawButton(m_TextureID, m_Position.x, m_Position.y, m_Position.w, m_Position.h, 100, 100);
        }

        void Update(){
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x < m_Position.x + 100 && x > m_Position.x && y < m_Position.y + 100 && y > m_Position.y){
                if (Input::getInstance() -> GetMouseButtonDown(1)){
                    m_State = CLICKED;
                }else{
                    m_State = HOVER;
                }
            }else{
                m_State = NORMAL;
            }
        }

        button_state GetState(){
            return m_State;
        }

    private:
        button_state m_State;
        SDL_Rect m_Position;
        std::string m_TextureID;
};
#endif