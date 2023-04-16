#include "Map/MapParser.h"

#include <iostream>

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load(std::string id, std::string source){
    //currently only use 1 map and 1 lv
    return Parse(id, source);
}
void MapParser::Clean(){
    std::map<std::string, GameMap*> :: iterator it;
        for (it = m_MapDict.begin(); it != m_MapDict.end(); it++){
            it -> second = nullptr;
        }
    m_MapDict.clear();
}   

bool MapParser::Parse(std::string id, std::string source){
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()){
        std::cerr << "Failed to load: " << source << '\n';
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;
    
    root -> Attribute("width", &colcount);
    root -> Attribute("height",&rowcount);
    root -> Attribute("tilewidth", &tilesize);
    TilesetList tilesets;
    for (TiXmlElement* e = root -> FirstChildElement(); e!= nullptr; e = e -> NextSiblingElement()){
        if (e -> Value() == std::string("tileset")){
            tilesets.push_back(ParseTileset(e));
        }
    }

    GameMap* gamemap = new GameMap();
    for (TiXmlElement* e = root -> FirstChildElement(); e!= nullptr; e = e -> NextSiblingElement()){
        if (e -> Value() == std::string("layer")){
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap -> m_MapLayers.push_back(tilelayer);
        }
    }

    m_MapDict[id] = gamemap;

    return true;
}
Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset){
    Tileset tileset;
    tileset.Name = xmlTileset -> Attribute("name");
    
    xmlTileset -> Attribute("firstgid", &tileset.FirstID);
    xmlTileset -> Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = tileset.FirstID + tileset.TileCount - 1;
    xmlTileset -> Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    xmlTileset -> Attribute("tilewidth", &tileset.TileSize);
    TiXmlElement* image = xmlTileset -> FirstChildElement();
    // std::cout << image -> Attribute("source") << '\n';
    tileset.Source = image -> Attribute("source");
    // std::cout << tileset.TileCount << " " << tileset.FirstID << " " << tileset.LastID << '\n';
    // std::cout << tileset.RowCount << " " << tileset.ColCount << " " << tileset.Name << '\n';
    // std::cout << tileset.TileSize << " " << tileset.Source << '\n';
    return tileset;    
}
TileLayer* MapParser::ParseTileLayer (TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount){
    TiXmlElement* data;
    for(TiXmlElement* e = xmlLayer -> FirstChildElement(); e!= nullptr; e = e -> NextSiblingElement()){
        if (e->Value() == std::string("data")){
            data = e;
            break;
        }    
    }
    std::string matrix(data -> GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
    for(int row = 0; row < rowcount; row++){
        for (int col = 0; col < colcount; col++){
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];
            if (!iss.good())
                break;
        }
    }
    // for(int row = 0; row < rowcount; row++){
    //     for (int col = 0; col < colcount; col++){
    //         std::cout << tilemap[row][col] << ',';
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << "--------------------------------------------\n";
    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}