#ifndef ASHARP_H
#define ASHARP_H

#include <cmath>
#include <stack>
#include <cstring>
#include <stdio.h>

#include "Maze.h"

class ASharp{
public:
    ///Variables
    bool closedList[globals::WIDTH/globals::BLOCK_SIZE][globals::HEIGHT/globals::BLOCK_SIZE];
    std::vector<block> openList;

    ///Methods
    ASharp(Maze *NMZ);

private:
    ///Variables
    Maze *MZ;
    std::vector<block> path;

    ///Methods
    double CalculateHeuristic(int x, int y, sf::Vector2i pos);
    std::vector<block> makePath();
};

#endif // ASHARP_H
