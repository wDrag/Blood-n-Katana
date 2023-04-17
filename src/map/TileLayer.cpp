#include "Map/TileLayer.h"
#include "Graphics/TextureManager.h"

#include <iostream>
#include <fstream>

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets) : m_Tilesets (tilesets){

    m_TileSize = tilesize;
    m_RowCount = rowcount;
    m_ColCount = colcount;
    m_TileMap = tilemap;
    m_Tilesets = tilesets;

    for (int i = 0; i < m_Tilesets.size(); i++){
        TextureManager::GetInstance() -> Load(m_Tilesets[i].Name, "src/resources/Map/"+ m_Tilesets[i].Source);
    }


}

void TileLayer::Render(){
std::fstream fo("log.txt", std::ios::out | std::ios::app);
    for (int i = 0; i < m_RowCount; i++){
        for (int j = 0; j < m_ColCount; j++){
            int tileID = m_TileMap[i][j];
            if (tileID == 0){
                continue;
            }
            int index = 0;
            if (m_Tilesets.size() > 1){
                for (int k = 1; k < m_Tilesets.size(); k++){
                    if(tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID){
                        tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                        index = k;
                        break;
                    }
                }
            }
            Tileset ts = m_Tilesets[index];
            int tileRow = tileID/ts.ColCount;
            int tileCol = tileID % ts.ColCount - 1;
            if(tileID % ts.ColCount == 0){
                tileRow--;
                tileCol = ts.ColCount - 1;
            }
            fo << i << " " << j << " " << tileID << " " << tileRow << " " << tileCol << '\n';
            TextureManager::GetInstance() -> DrawTile(ts.Name, ts.TileSize, j, i, tileRow, tileCol);
        }
    }
fo << "-0-0------------------------------------------------0-0-\n";
}
void TileLayer::Update(){
    //do nothing yet
}