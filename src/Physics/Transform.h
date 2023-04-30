#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Physics/Vector2D.h"

class Transform{
    public:
        float X, Y;

        Transform(float x = 0.0f, float y = 0.0f){
            X = x;
            Y = y;
        }
        inline void TranslateX(float x){
            X += x;
        }
        inline void TranslateY(float y){
            Y += y;
        }
        inline void Translate(Vector2D v){
            X += v.X;
            Y += v.Y;
        }
};

#endif