#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file)
    : tileWidth(tileWidth), tileHeight(tileHeight), tileSet(file){

    if(tileSet.IsOpen()){
        columns = tileSet.GetWidth() / tileWidth;
        rows = tileSet.GetHeight() / tileHeight;
    } else{
        columns = 0;
        rows = 0;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y){
    unsigned maxTiles = rows * columns;
    if(index < maxTiles){
        int tileColumn = index % columns;
        int tileRow = index / columns;

        int clipX = tileColumn * tileWidth;
        int clipY = tileRow * tileHeight;

        tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
        tileSet.Render(x, y, tileWidth, tileHeight);
    }
}

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}