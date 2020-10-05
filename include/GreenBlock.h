#ifndef GREENBLOCK_H
#define GREENBLOCK_H

#include <SFML/Graphics.hpp>
#include "globals.h"
#include "Maze.h"

class GreenBlock{
public:
    ///Variables

    ///Methods
    GreenBlock();
    void Move(int direction, Maze *MZ);

private:
    ///Variables

    ///Methods
    void MoveSetFillColor(int direction, Maze *MZ);
};

#endif // GREENBLOCK_H
