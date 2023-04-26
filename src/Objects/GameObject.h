#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Objects/IObject.h"
#include "Physics/Transform.h"
#include "Physics/Point.h"

#include <string>
#include <SDL2/SDL.h>

struct Properties{

    Properties(std::string textureID, int width, int height, float x = 0.0f, float y = 0.0f){
        X = x;
        Y = y;
        Width = width;
        Height = height;
        TextureID = textureID;

    }

    public:
        std::string TextureID;
        int Width, Height;
        float X, Y;
};

class GameObject : public IObject{
    public:
        GameObject(Properties* props): m_TextureID(props->TextureID),
        m_Width(props->Width), m_Height(props->Height){
        m_Transform = new Transform(props->X, props->Y);
        float px = props -> X + props -> Width / 2;
        float py = props -> Y + props -> Height / 2;
        m_Origin = new Point(px, py);
        }
        virtual ~GameObject(){}
        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
        inline Point* GetOrigin(){return m_Origin;}
    protected:
        Point* m_Origin;
        Transform* m_Transform;
        int m_Width, m_Height;
        std::string m_TextureID;
};

#endif