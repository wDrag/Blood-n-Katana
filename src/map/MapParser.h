#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "Map/GameMap.h"
#include "Map/TileLayer.h"
#include "TinyXML/tinyxml.h"

class MapParser{
    public:
        bool Load(std::string id, std::string source);
        void Clean();

        inline GameMap* GetMaps(std::string id){return m_MapDict[id];}
        inline static MapParser* GetInstance() {return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();}
        
    private:
        MapParser(){}
        bool Parse(std::string id, std::string source);
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer (TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);
        static MapParser* s_Instance;
        std::map<std::string, GameMap*> m_MapDict; 
};

#endif