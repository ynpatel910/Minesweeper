#ifndef Tile_h
#define Tile_h
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class Tile {
    bool Reveal = false;
    bool Live_Mine = false;
    bool Live_Flagged = false;
    int Live_Mines = 0;
    vector<Tile*> Vect_Tiles;
    sf::Sprite* sprite = new sf::Sprite;
    sf::Sprite* sprite2 = new sf::Sprite;
    sf::Sprite* Sprite_Flag = new sf::Sprite;
public:
    Tile(sf::Texture& texture, sf::Texture& Texture_flag);
    sf::Sprite* Sprite_Get() { return sprite; }
    sf::Sprite* Sprite_Get2() { return sprite2; }
    sf::Sprite* Sprite_GetFlag() { return Sprite_Flag; }
    bool Mine_Get() { return Live_Mine; }
    bool Mine_Revealed() { return Reveal; }
    bool Mine_Flagged() { return Live_Flagged; }
    int Get_LiveMines() { return Live_Mines; }
    vector<Tile*>* Get_LiveTiles() { return &Vect_Tiles; }
    void Adjacent_Tiles(vector<Tile*>& Tiles_Adj);
    void Mine_Set(bool place) { Live_Mine = place; }
    void Reveal_Set(bool place) { Reveal = place; }
    void Flag_Set(bool place) { Live_Flagged = place; }
    void Sprites_Move(float x, float y);
    void Mine_Make();
};

#endif
