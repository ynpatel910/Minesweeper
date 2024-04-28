#include "Tile.h"
#include <iostream>

Tile::Tile(sf::Texture& texture, sf::Texture& Texture_flag) {
    sprite->setTexture(texture);
    sprite2->setTexture(texture);
    Sprite_Flag->setTexture(Texture_flag);
}

void Tile::Sprites_Move(float y, float x) {
    sprite->move(sf::Vector2f(y, x));
    sprite2->move(sf::Vector2f(y, x));
    Sprite_Flag->move(sf::Vector2f(y, x));
}

void Tile::Mine_Make() {
    Live_Mine = true;
}

void Tile::Adjacent_Tiles(vector<Tile*>& Tiles_Adj) {
    Vect_Tiles = Tiles_Adj;
    Live_Mines = 0;
    for (int i = 0; i < Tiles_Adj.size(); i++) {
        Tile* Tile1 = Tiles_Adj.at(i)
            ;        if (Tile1->Mine_Get()) {
            Live_Mines++;
        }
    }
}