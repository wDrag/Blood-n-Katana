#include "Button/Button.h"

Buttons* Buttons::s_Instance = nullptr;

void Buttons::AddButton(int x, int y, std::string textureID){
    m_Buttons.push_back(new Button(x, y, textureID));
}

void Buttons::Draw(){
    for (int i = 0; i < m_Buttons.size(); i++){
        m_Buttons[i] -> Draw();
    }
}

void Buttons::Update(){
    for (int i = 0; i < m_Buttons.size(); i++){
        m_Buttons[i] -> Update();
    }
}