#ifndef CAMERA_H
#define CAMERA_H

#include "SDL2/SDL.h"
#include "Physics/Point.h"
#include "Physics/Vector2D.h"
#include "Globals/Globals.h"

class Camera{
    public:
        inline static Camera* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
        }

        void Update(float dt);
        inline SDL_Rect GetViewBox(){return m_ViewBox;}
        inline Vector2D GetPosition(){return m_Position;}
        inline void setTarget(Point* target){m_Target = target;}

    private:
        Camera(){ m_ViewBox = {0, 0, Globals::GetInstance() -> SCREEN_WIDTH, Globals::GetInstance() -> SCREEN_HEIGHT}; }

        Point* m_Target = new Point();
        Vector2D m_Position = Vector2D();
        SDL_Rect m_ViewBox = SDL_Rect();
        
        static Camera* s_Instance;
};

#endif