#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <float.h>
#include <iostream>

#include "block.h"
#include "globals.h"

class Maze{
public:
    ///Variables
    std::vector<std::vector<block>> maze;
    sf::Vector2i greenPos;
    sf::Vector2i centerPos;

    ///Methods
    Maze();
    void Draw(sf::RenderWindow &renderWindow);
    bool IsMazeSolved();
    bool PartOfCenter(int x, int y);
    bool SquareIsValid(sf::Vector2i pos);
    bool SquareIsValid(sf::Color col);

private:
    ///Variables
    sf::Vector2f start;

    ///Methods
    sf::Vector2f StartingPoint();
    std::vector<sf::Vector2i> CreateBlockExceptions();
    bool PartOfCircle(int x, int y);
};

#endif // MAZE_H
