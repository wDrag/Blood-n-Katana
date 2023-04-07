#include "Map/TileLayer.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets){
    m_TileSize = tilesize;
    m_RowCount = rowcount;
    m_ColCount = colcount;
    m_TileMap = tilemap;
    m_TileSets = tilesets;
}

virtual void TileLayer::Render(){

}
virtual void TileLayer::Update(){

}