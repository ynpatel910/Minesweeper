#ifndef Board_h
#define Board_h

#include "Tile.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Board {
    Tile* tiles[16][25];
    int Count_Mine = 0;
    bool D_Mode = false;
    bool Game_Lost = false;
    bool Game_Win = false;
    int Safe_Spaces = 400;
    sf::Texture Digs, debug, Face_Happy, Face_Lose, Face_Win, Flag, Mine, Num_1, Num_2, Num_3, Num_4, Num_5, Num_6, Num_7, Num_8, T_1, T_2, T_3, Hidden_Tile, Tile_Revealed;
    sf::Sprite Sprice_Face, Sprice_Debug, T_1Sprite, T_2Sprite, T_3Sprite;
    string score = "000";
    sf::Sprite Score_1, Score_2, Score_3;
public:
    Board();
    ~Board();
    void Print_Board(sf::RenderWindow& Window);
    Tile* Tile_Get(int R, int C);
    void Score_Update();
    void Score_Add(int Score_Add);
    void Tile_Adj();
    void Text_Set(sf::Sprite* spell, sf::Texture& Letters);
    void Mine_Gen();
    void Board_Set();
    void File_Load(string File_Name);
    void Mouse_Click(int x, int y, string type);
    void Reveal_Tiles(Tile* tile);
    void Tile_Flagged(Tile* tile);
    void Game_End();
    void Won_Game();
};

#endif 