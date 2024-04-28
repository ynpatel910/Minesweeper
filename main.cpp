#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Tile.h"
#include "Board.h"


using namespace std;

int main() {

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Minesweeper");

    Board board;
    while (Window.isOpen())
    {

        sf::Event event;
        while (Window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                Window.close();
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    board.Mouse_Click(event.mouseButton.x, event.mouseButton.y, "left");
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    board.Mouse_Click(event.mouseButton.x, event.mouseButton.y, "right");
                }
            }
        }
        Window.clear();
        board.Print_Board(Window);
        Window.display();
    }

    return 0;
}