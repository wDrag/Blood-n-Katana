#ifndef CHARMANAGEMENT_H
#define CHARMANAGEMENT_H

#include <map>
#include <vector>
#include <string>
#include "TinyXML/tinyxml.h"

struct Stats{
    int HP;
    int ATK;
    float mod1, mod2, mod3;
};

class CM{
    public:
        static CM* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new CM();
        }
        void StatsParser(std::string source, std::string value);
        void StatsClean();
        inline Stats GetStats(std::string value) {return m_CharMap[value];}
    private:
        CM(){};
        static CM* s_Instance;
        std::map<std::string, Stats> m_CharMap;
};

#endif