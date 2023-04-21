#include "Map/TileLayer.h"
#include "Graphics/TextureManager.h"


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
             TextureManager::GetInstance() -> DrawTile(ts.Name, ts.TileSize, j, i, tileRow, tileCol);
        }
    }
}
void TileLayer::Update(){
    //do nothing yet
}