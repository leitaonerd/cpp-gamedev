#pragma once
#include <string>
#include "Sprite.h"

class TileSet {
    private:
        Sprite tileSet;
        int tileWidth;
        int tileHeight;
        int tileCount;

        int rows;
        int columns;

    public:
        TileSet(int tileWidth, int tileHeight, std::string file);
        void RenderTile(unsigned index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();
}