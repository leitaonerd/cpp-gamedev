#include "TileMap.h"
#include "GameObject.h"
#include <fstream>
#include <sstream>
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) 
    : Component(associated) {
    SetTileSet(tileSet);
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cerr << "Erro ao abrir o mapa: " << file << std::endl;
        return;
    }

    std::string token;
    
    std::getline(f, token, ',');
    mapWidth = std::stoi(token);
    
    std::getline(f, token, ',');
    mapHeight = std::stoi(token);
    
    std::getline(f, token, ',');
    mapDepth = std::stoi(token);

    int totalTiles = mapWidth * mapHeight * mapDepth;
    
    for (int i = 0; i < totalTiles; i++) {
        std::getline(f, token, ',');
        tileMatrix.push_back(std::stoi(token) - 1);
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    // O unique_ptr assume a posse do ponteiro usando reset
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    // Converte a coordenada 3D num índice de matriz unidimensional
    int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer) {
    for (int x = 0; x < mapWidth; x++) {
        for (int y = 0; y < mapHeight; y++) {
            
            float posX = x * tileSet->GetTileWidth();
            float posY = y * tileSet->GetTileHeight();
            
            posX += associated.box.x;
            posY += associated.box.y;
            
            int tileIndex = At(x, y, layer);
            
            if (tileIndex > -1) {
                tileSet->RenderTile(tileIndex, posX, posY);
            }
        }
    }
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; z++) {
        RenderLayer(z);
    }
}

void TileMap::Update(float dt) {
    //implementar depois
}

int TileMap::GetWidth() { return mapWidth; }
int TileMap::GetHeight() { return mapHeight; }
int TileMap::GetDepth() { return mapDepth; }