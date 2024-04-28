#include "Board.h"
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

Board::Board() {
    if (!Digs.loadFromFile("images/digits.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!debug.loadFromFile("images/debug.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Face_Happy.loadFromFile("images/face_happy.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Face_Lose.loadFromFile("images/face_lose.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Face_Win.loadFromFile("images/face_win.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Flag.loadFromFile("images/flag.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Mine.loadFromFile("images/mine.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Num_1.loadFromFile("images/number_1.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Num_2.loadFromFile("images/number_2.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Num_3.loadFromFile("images/number_3.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Num_4.loadFromFile("images/number_4.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Num_5.loadFromFile("images/number_5.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Num_6.loadFromFile("images/number_6.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Num_7.loadFromFile("images/number_7.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Num_8.loadFromFile("images/number_8.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!T_1.loadFromFile("images/test_1.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!T_2.loadFromFile("images/test_2.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!T_3.loadFromFile("images/Test_3.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Hidden_Tile.loadFromFile("images/tile_hidden.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!Tile_Revealed.loadFromFile("images/tile_revealed.png"))
    {
        cout << "Error loading File..." << endl;
    }

    Sprice_Face.setTexture(Face_Happy);
    Sprice_Face.move(sf::Vector2f(6 * 64, 32 * 16));
    Sprice_Debug.setTexture(debug);
    Sprice_Debug.move(sf::Vector2f(8 * 64, 32 * 16));
    T_1Sprite.setTexture(T_1);
    T_1Sprite.move(sf::Vector2f(9 * 64, 32 * 16));
    T_2Sprite.setTexture(T_2);
    T_2Sprite.move(sf::Vector2f(10 * 64, 32 * 16));
    T_3Sprite.setTexture(T_3);
    T_3Sprite.move(sf::Vector2f(11 * 64, 32 * 16));
    Score_1.move(sf::Vector2f(0, 32 * 16));
    Score_1.setTexture(Digs);
    Score_2.move(sf::Vector2f(21, 32 * 16));
    Score_2.setTexture(Digs);
    Score_3.move(sf::Vector2f(42, 32 * 16));
    Score_3.setTexture(Digs);
    Board_Set();
}

Board::~Board() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            delete tiles[i][j];
        }
    }
}

void Board::Print_Board(sf::RenderWindow& Window) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            Tile* tile = tiles[i][j];
            sf::Sprite* spell = tile->Sprite_Get();
            sf::Sprite* sprite2 = tile->Sprite_Get2();
            if (Game_Lost) {
                if (tile->Mine_Revealed()) {
                    Window.draw(*spell);
                    Window.draw(*sprite2);
                }
                else {
                    if (tile->Mine_Get()) {
                        Text_Set(spell, Tile_Revealed);
                        Window.draw(*spell);
                        Window.draw(*sprite2);
                    }
                    else {
                        Window.draw(*spell);
                    }
                }
            }
            else if (Game_Win) {
                if (tile->Mine_Revealed()) {
                    Window.draw(*spell);
                    Window.draw(*sprite2);
                }
                else {
                    if (tile->Mine_Get()) {
                        Window.draw(*spell);
                        Window.draw(*tile->Sprite_GetFlag());
                    }
                }
            }
            else {
                if (D_Mode) {
                    Window.draw(*spell);
                    if (tile->Mine_Get() || tile->Mine_Revealed()) {
                        Window.draw(*sprite2);
                    }
                    if (tile->Mine_Flagged() && !tile->Mine_Revealed()) {
                        Window.draw(*tile->Sprite_GetFlag());
                    }
                }
                else {
                    if (tile->Mine_Revealed()) {
                        Window.draw(*spell);
                        Window.draw(*sprite2);
                    }
                    else {
                        Window.draw(*spell);
                        if (tile->Mine_Flagged()) {
                            Window.draw(*tile->Sprite_GetFlag());
                        }
                    }
                }
            }
        }
    }
    Score_Update();
    Window.draw(Sprice_Face);
    Window.draw(Sprice_Debug);
    Window.draw(T_1Sprite);
    Window.draw(T_2Sprite);
    Window.draw(T_3Sprite);
    Window.draw(Score_1);
    Window.draw(Score_2);
    Window.draw(Score_3);
}

void Board::Board_Set() {
    Game_Lost = false;
    Game_Win = false;
    Safe_Spaces = 400;
    Text_Set(&Sprice_Face, Face_Happy);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if (!tiles[i][j]) {
                delete tiles[i][j];
            }
            tiles[i][j] = new Tile(Hidden_Tile, Flag);
            tiles[i][j]->Sprites_Move(j * 32, i * 32);
        }
    }
    Count_Mine = 0;
    Mine_Gen();
    Tile_Adj();
}

void Board::Mine_Gen() {
    srand(time(NULL));
    while (Count_Mine < 50) {
        //srand (time(NULL));
        int Rand1 = rand() % 16;
        int Rand2 = rand() % 25;
        Tile* tile = tiles[Rand1][Rand2];
        if (!tile->Mine_Get()) {
            tile->Mine_Make();
            Text_Set(tile->Sprite_Get2(), Mine);
            Count_Mine++;
            Safe_Spaces -= 1;
        }
    }
}

void Board::File_Load(string filename) {
    char ch;
    fstream File_Name(filename, fstream::in);
    int i = 0;
    int j = 0;
    Count_Mine = 0;
    Safe_Spaces = 400;
    while (File_Name >> ch) {
        Tile* tile = tiles[i][j];
        Text_Set(tile->Sprite_Get(), Hidden_Tile);
        if (ch == '0') {
            tile->Mine_Set(false);
            tile->Reveal_Set(false);
            Text_Set(tile->Sprite_Get2(), Tile_Revealed);
        }
        else if (ch == '1') {
            tile->Mine_Set(true);
            Safe_Spaces -= 1;
            tile->Reveal_Set(false);
            Count_Mine++;
            Text_Set(tile->Sprite_Get2(), Mine);
        }
        j++;
        if (j > 24) {
            j = 0;
            i++;
        }
    }
    Tile_Adj();
}

void Board::Tile_Adj() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            vector<Tile*> Tiles_Adj;
            if (i - 1 >= 0) {
                if (j + 1 < 25) {
                    Tile* tile = tiles[i - 1][j + 1];
                    Tiles_Adj.push_back(tile);
                }
                if (j - 1 >= 0) {
                    Tile* tile = tiles[i - 1][j - 1];
                    Tiles_Adj.push_back(tile);
                }
                Tile* tile = tiles[i - 1][j];
                Tiles_Adj.push_back(tile);
            }
            if (i + 1 < 16) {
                if (j + 1 < 25) {
                    Tile* tile = tiles[i + 1][j + 1];
                    Tiles_Adj.push_back(tile);
                }
                if (j - 1 >= 0) {
                    Tile* tile = tiles[i + 1][j - 1];
                    Tiles_Adj.push_back(tile);
                }
                Tile* tile = tiles[i + 1][j];
                Tiles_Adj.push_back(tile);
            }
            if (j + 1 < 25) {
                Tile* tile = tiles[i][j + 1];
                Tiles_Adj.push_back(tile);
            }
            if (j - 1 >= 0) {
                Tile* tile = tiles[i][j - 1];
                Tiles_Adj.push_back(tile);
            }
            Tile* Tile1 = tiles[i][j];
            Tile1->Adjacent_Tiles(Tiles_Adj);
            if (Tile1->Mine_Get()) {
                Text_Set(Tile1->Sprite_Get2(), Mine);
            }
            else {
                int adjMineCount = Tile1->Get_LiveMines();
                switch (adjMineCount) {
                case 0:
                    Text_Set(Tile1->Sprite_Get2(), Tile_Revealed);
                    break;
                case 1:
                    Text_Set(Tile1->Sprite_Get2(), Num_1);
                    break;
                case 2:
                    Text_Set(Tile1->Sprite_Get2(), Num_2);
                    break;
                case 3:
                    Text_Set(Tile1->Sprite_Get2(), Num_3);
                    break;
                case 4:
                    Text_Set(Tile1->Sprite_Get2(), Num_4);
                    break;
                case 5:
                    Text_Set(Tile1->Sprite_Get2(), Num_5);
                    break;
                case 6:
                    Text_Set(Tile1->Sprite_Get2(), Num_6);
                    break;
                case 7:
                    Text_Set(Tile1->Sprite_Get2(), Num_7);
                    break;
                case 8:
                    Text_Set(Tile1->Sprite_Get2(), Num_8);
                    break;
                }
            }
        }
    }
}

void Board::Score_Update() {
    int flaggedMines = 0;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            Tile* Tile1 = tiles[i][j];
            if (Tile1->Mine_Flagged()) {
                flaggedMines++;
            }
        }
    }
    int curScore = Count_Mine - flaggedMines;
    score = to_string(curScore) + "";
    char digit1 = score[0];
    if (digit1 == '-') {
        Score_1.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
    }
    else {
        int dig1 = digit1 - 48;
        Score_1.setTextureRect(sf::IntRect(21 * dig1, 0, 21, 32));
    }
    char digit2 = score[1];
    int dig2 = digit2 - 48;
    Score_2.setTextureRect(sf::IntRect(21 * dig2, 0, 21, 32));
    char digit3 = score[2];
    int dig3 = digit3 - 48;
    Score_3.setTextureRect(sf::IntRect(21 * dig3, 0, 21, 32));
}

void Board::Score_Add(int Score_Add) {
    int curScore = stoi(score);
    curScore = curScore + Score_Add;
    score = "" + to_string(curScore);
}

Tile* Board::Tile_Get(int R, int C) {
    return tiles[R][C];
}

void Board::Text_Set(sf::Sprite* spell, sf::Texture& Letters) {
    spell->setTexture(Letters);
}


void Board::Mouse_Click(int x, int y, string Click) {
    if (y > 512 && y < 578) {

        if (x >= (64 * 6) && x <= (64 * 7)) {
            Board_Set();
        }
        else if (x >= (64 * 8) && x < (64 * 9) && !Game_Lost && !Game_Win) {
            if (D_Mode) { D_Mode = false; }
            else { D_Mode = true; }
        }
        else if (x >= (64 * 9) && x < (64 * 10) && !Game_Lost && !Game_Win) {
            File_Load("boards/testboard1.brd");
        }
        else if (x >= (64 * 10) && x < (64 * 11) && !Game_Lost && !Game_Win) {
            File_Load("boards/testboard2.brd");
        }
        else if (x >= (64 * 11) && x < (64 * 12) && !Game_Lost && !Game_Win) {
            File_Load("boards/testboard3.brd");
        }
    }
    else if (!Game_Lost && !Game_Win) {
        //Game Board. Work on revealing
        int R = y / 32;
        int C = x / 32;
        Tile* Tile1 = tiles[R][C];
        if (Click == "left") {
            if (!Tile1->Mine_Flagged() && !Tile1->Mine_Revealed()) {
                Reveal_Tiles(Tile1);
            }
        }
        else if (Click == "right") {
            Tile_Flagged(Tile1);
        }
        else {
            cout << "Wrong click type given" << endl;
        }
    }

}

void Board::Tile_Flagged(Tile* tile) {
    if (tile->Mine_Flagged()) {
        tile->Flag_Set(false);
    }
    else {
        tile->Flag_Set(true);
    }
}

void Board::Reveal_Tiles(Tile* tile) {
    tile->Reveal_Set(true);
    Text_Set(tile->Sprite_Get(), Tile_Revealed);
    if (tile->Mine_Get()) {
        Game_End();
    }
    else {
        Safe_Spaces -= 1;
        if (Safe_Spaces <= 0) {
            Won_Game();
        }
        if (tile->Get_LiveMines() == 0) {
            vector<Tile*>* Tiles_Adj = tile->Get_LiveTiles();
            int size = Tiles_Adj->size();
            for (int i = 0; i < size; i++) {
                Tile* adjTile = Tiles_Adj->at(i);
                if (!adjTile->Mine_Revealed()) {
                    Reveal_Tiles(adjTile);
                }
            }
        }
    }
}

void Board::Game_End() {
    Game_Lost = true;
    D_Mode = false;
    Text_Set(&Sprice_Face, Face_Lose);
}

void Board::Won_Game() {
    Game_Win = true;
    D_Mode = false;
    Text_Set(&Sprice_Face, Face_Win);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            Tile* tile = tiles[i][j];
            if (tile->Mine_Revealed()) {
                tile->Flag_Set(false);
            }
            else {
                tile->Flag_Set(true);
            }
        }
    }
}