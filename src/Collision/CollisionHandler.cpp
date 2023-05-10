#include <Collision/CollisionHandler.h>
#include "Core/engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler(){
    m_CollisionLayer = (TileLayer*)Engine::GetInstance() -> GetMap() -> GetMapLayers().back();
    m_PlatformTilemap = m_CollisionLayer -> GetTileMap();
}   

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b){
    bool x_overlaps = ((a.x < b.x + b.w) && (a.x + a.w > b.x)) || ((b.x < a.x + a.w) && (b.x + b.w > a.x));
    bool y_overlaps = ((a.y < b.y + b.h) && (a.y + a.h > b.y)) || ((b.y < a.y + a.h) && (b.y + b.h > a.y));
    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a){
    int TileSize = 48;
    int RowCount = 20;
    int ColCount = 60;

    int left_tile = a.x / TileSize;
    int right_tile = (a.x + a.w) / TileSize;
    
    int top_tile = a.y / TileSize;
    int bottom_tile = (a.y + a.h) / TileSize;

    if (left_tile < 0) left_tile = 0;
    if (right_tile > ColCount) right_tile = ColCount;

    if (top_tile < 0) top_tile = 0;
    if (bottom_tile > RowCount) bottom_tile = RowCount;

    for (int i = left_tile; i <= right_tile; i++){
        for (int j = top_tile; j <= bottom_tile; j++){
            if (m_PlatformTilemap[j][i] > 0) 
                return true;
        }
    }

    return false;
}