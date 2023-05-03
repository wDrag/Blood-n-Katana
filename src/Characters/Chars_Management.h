#ifndef CHARMANAGEMENT_H
#define CHARMANAGEMENT_H

#include "Characters/Boss_Vampire.h"
#include "Characters/Samurai.h"

class CM{
    public:
        CM* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new CM();
        }
    private:
        CM(){};
        static CM* s_Instance;
};

#endif