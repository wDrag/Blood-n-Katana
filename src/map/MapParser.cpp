#include "Map/MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load(std::string id, std::string source){
    id = "lv1";
    source = "src/resources/Map/Map1.tmx";
    //currently only use 1 map and 1 lv
    return Parse(id, source);
}
void MapParser::Clean(){

}

GameMap MapParser::GetMaps(){

}

bool MapParser::Parse(std::string id, std::string source){

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
    tileset.Source = image -> Attribute("source");
    return tileset;    
}
TileLayer MapParser::ParseTileLayer (TiXmlElement* xmlLayer){

}